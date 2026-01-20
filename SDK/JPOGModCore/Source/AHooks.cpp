#include "pch.h"
#include "AHooks.h"
#include "HookHelpers.h"
#include "AModLoader.h"

#include <TRender/TModel.h>

#include <JPOGSDK/Interface.h>
#include <JPOGSDK/SDKHooks.h>

#include <unordered_map>
#include <string>

TOSHI_NAMESPACE_USING

static TBOOL s_bIsLoadingModel = TFALSE;

static void HooksPrint(const TCHAR *a_pchFormat, ...)
{
	TCHAR s_szBuffer[512];

	va_list list;
	va_start(list, a_pchFormat);
	vsprintf_s(s_szBuffer, a_pchFormat, list);
	va_end(list);

	printf(s_szBuffer);
}

MEMBER_HOOK(Interface::TKernelInterface + 0xb360, Toshi::TModel, TFileManager_CreateFile, Toshi::TFile *, const Toshi::TCString &a_strName, TUINT a_uiMode)
{
	HooksPrint("[ModCore] TFileManager::CreateFile (file=%s; mode=%u)\n", a_strName.GetString(), a_uiMode);

	return CallOriginal(a_strName, a_uiMode);
}

static Toshi::TMaterialLibraryManager         *s_pMatLibManager; // TODO: replace with a value from TRenderInterface
static std::unordered_map<std::string, void *> s_mapMatLibs;
static std::unordered_map<void *, std::string> s_mapMatLibsNames;

MEMBER_HOOK(Interface::TRenderInterface + 0xd980, Toshi::TMaterialLibraryManager, TMaterialLibraryManager_LoadMaterialLibrary, void *, const TCHAR *a_pchFileName)
{
	HooksPrint("[ModCore] TMaterialLibraryManager::LoadMaterialLibrary (file=%s)\n", a_pchFileName);

	// HACK:
	s_pMatLibManager = this;

	auto it = s_mapMatLibs.find(a_pchFileName);
	if (it == s_mapMatLibs.end())
	{
		void *pMatLib = CallOriginal(a_pchFileName);
		if (pMatLib && pMatLib != (void *)-1)
		{
			s_mapMatLibs[a_pchFileName] = pMatLib;
			s_mapMatLibsNames[pMatLib]  = a_pchFileName;
		}
		else
		{
			HooksPrint("[ModCore] Couldn't load requested TMaterialLibrary\n");
		}

		return pMatLib;
	}

	HooksPrint("[ModCore] Requested TMaterialLibrary already exists!!!\n", a_pchFileName);
	return it->second;
}

MEMBER_HOOK(Interface::TRenderInterface + 0xd9f0, Toshi::TMaterialLibraryManager, TMaterialLibraryManager_UnloadMaterialLibrary, void, void *a_pMatLib)
{
	HooksPrint("[ModCore] TMaterialLibraryManager::UnloadMaterialLibrary (matlib=%p)\n", a_pMatLib);

	// HACK:
	s_pMatLibManager = this;

	auto it = s_mapMatLibsNames.find(a_pMatLib);
	if (it != s_mapMatLibsNames.end())
	{
		s_mapMatLibs.erase(it->second);
		s_mapMatLibsNames.erase(a_pMatLib);
	}

	CallOriginal(a_pMatLib);
}

MEMBER_HOOK(Interface::TKernelInterface + 0x14c90, Toshi::TKernelInterface, TKernelInterface_LoadInterface, void *, const Toshi::TCString &a_strName)
{
	HooksPrint("[ModCore] TKernelInterface::LoadInterface (file=%s)\n", a_strName.GetString());

	// Patch name of the dll, since exe name is referenced by the Units.dll
	if (a_strName == "Units") return CallOriginal("JPModUnits");

	return CallOriginal(a_strName);
}

MEMBER_HOOK(Interface::TRenderInterface + 0x9730, Toshi::TModel, TModel_LoadTMD, TBOOL, const TCHAR *a_pchFileName)
{
	HooksPrint("[ModCore] TModel::LoadTMD (name=%s)\n", a_pchFileName);

	s_bIsLoadingModel = TTRUE;

	if (s_pMatLibManager)
	{
		// Try loading a material library for this model
		static TCHAR s_ModelBuffer[128];

		const TCHAR *pchNameStart = strrchr(a_pchFileName, '/') + 1;
		if (!pchNameStart) pchNameStart = strrchr(a_pchFileName, '\\') + 1;
		if (!pchNameStart) pchNameStart = a_pchFileName;

		const TCHAR *pchExtStart = strrchr(a_pchFileName, '.');
		if (pchNameStart && *pchNameStart && pchExtStart && *pchExtStart)
		{
			strncpy(s_ModelBuffer, pchNameStart, pchExtStart - pchNameStart);
			s_ModelBuffer[pchExtStart - pchNameStart] = '\0';

			TINT iModelLength = strlen(s_ModelBuffer);
			if (iModelLength >= 3
				&& (strcmp(s_ModelBuffer + iModelLength - 3, "_lo") == 0 ||
					strcmp(s_ModelBuffer + iModelLength - 3, "_md") == 0 ||
					strcmp(s_ModelBuffer + iModelLength - 3, "_hi") == 0)
				) s_ModelBuffer[iModelLength - 3] = '\0';

			static TCHAR s_PathBuffer[MAX_PATH];
			sprintf_s(s_PathBuffer, "Data\\matlibs\\%s.tml", s_ModelBuffer);

			((TMaterialLibraryManager_LoadMaterialLibrary::_hook_obj*)(s_pMatLibManager))->_hook_func(s_PathBuffer);
		}
	}

	TBOOL bResult     = CallOriginal(a_pchFileName);
	s_bIsLoadingModel = TFALSE;

	return bResult;
}

//-----------------------------------------------------------------------------
// Patch to allow using any TKL at any digsite
//-----------------------------------------------------------------------------
struct TKeyframeLibraryManager {};
struct TKeyframeLibrary {};
MEMBER_HOOK(Interface::TRenderInterface + 0x6850, TKeyframeLibraryManager, TKeyframeLibraryManager_UnloadLibrary, void, TKeyframeLibrary *a_pKeyframeLibrary)
{
	HooksPrint("[ModCore] Preventing TKeyframeLibrary from destroying...\n");
}

MEMBER_HOOK(Interface::TRenderInterface + 0x5850, TKeyframeLibraryManager, TKeyframeLibraryManager_GetLibrary, TKeyframeLibrary *, const TCHAR *a_pchKeyLibName)
{
	HooksPrint("[ModCore] TKeyframeLibraryManager::GetLibrary (name=%s)\n", a_pchKeyLibName);

	TKeyframeLibrary *pResult = CallOriginal(a_pchKeyLibName);
	if (pResult) return pResult;

	// If the keyframe library wasn't found, need to load it
	HooksPrint("[ModCore] Couldn't find keyframe library, so will try to load it...\n");
	TCHAR s_szBuffer[MAX_PATH];
	sprintf_s(s_szBuffer, "Data\\Models\\%s.tkl", a_pchKeyLibName);

	// TKeyframeLibraryManager::LoadLibrary
	pResult = CALL_THIS(Interface::TRenderInterface + 0x57a0, TKeyframeLibraryManager *, TKeyframeLibrary *, this, const TCHAR *, s_szBuffer);

	if (!pResult) HooksPrint("[ModCore] Couldn't load the TKL file\n");

	return pResult;
}

void AHooks::Initialise()
{
	InstallHook<TMaterialLibraryManager_LoadMaterialLibrary>();
	InstallHook<TMaterialLibraryManager_UnloadMaterialLibrary>();
	InstallHook<TKernelInterface_LoadInterface>();
	InstallHook<TFileManager_CreateFile>();
	InstallHook<TModel_LoadTMD>();
	InstallHook<TKeyframeLibraryManager_UnloadLibrary>();
	InstallHook<TKeyframeLibraryManager_GetLibrary>();
}

