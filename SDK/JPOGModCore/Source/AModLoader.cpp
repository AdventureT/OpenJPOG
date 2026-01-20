#include "pch.h"
#include "AHooks.h"
#include "AModLoader.h"

#include <filesystem>

AModLoader::AModLoader()
	: m_fTotalTime(0.0f)
	, m_bLoaded(TFALSE)
	, m_uiNumMods(0)
{
}

AModLoader::~AModLoader()
{
}

TBOOL AModLoader::OnUpdate(TFLOAT a_fDeltaTime)
{
	for (auto it = m_LoadedMods.Begin(); it != m_LoadedMods.End(); it++)
	{
		TBOOL bResult = it->OnUpdate(a_fDeltaTime);
		TASSERT(bResult != TFALSE);
	}

	m_fTotalTime += a_fDeltaTime;
	return TTRUE;
}

TBOOL AModLoader::OnCreate()
{
	LoadMods();

	return TTRUE;
}

void AModLoader::LoadMods()
{
	TDPRINTF("Loading mods...\n");

	// Load the mods
	for (const auto &entry : std::filesystem::directory_iterator("Mods\\"))
	{
		if (entry.path().extension().compare(L".dll") == 0)
		{
			const wchar_t *dll = entry.path().native().c_str();

			char szDllPath[MAX_PATH];
			Toshi::TSystem::StringUnicodeToChar(szDllPath, entry.path().native().c_str(), -1);

			HMODULE hModule             = LoadLibraryW(dll);
			auto    fnCreateModInstance = TREINTERPRETCAST(t_CreateModInstance, GetProcAddress(hModule, "CreateModInstance"));
			auto    fnGetVersion        = TREINTERPRETCAST(t_GetModVersion, GetProcAddress(hModule, "GetModVersion"));
			auto    fnGetName           = TREINTERPRETCAST(t_GetModName, GetProcAddress(hModule, "GetModName"));

			// Load the mod
			if (fnCreateModInstance)
			{
				AModInstance *pModInstance = fnCreateModInstance();
				pModInstance->m_strName    = (fnGetName) ? fnGetName() : "Unknown Mod";
				pModInstance->m_uiVersion  = (fnGetVersion) ? fnGetVersion() : 0;

				if (pModInstance)
				{
					TDPRINTF("Trying to initialise '%s'\n", pModInstance->GetName());
					pModInstance->m_hModule = hModule;

					if (pModInstance->OnLoad())
					{
						TDPRINTF("Successfully initialised!\n");
						m_LoadedMods.InsertTail(pModInstance);
						m_uiNumMods += 1;
					}
					else
					{
						TERROR("Couldn't initialise!\n");
						delete pModInstance;
						FreeLibrary(hModule);
					}
				}
				else
				{

					TERROR("%s: CreateModInstance returned TFALSE!\n", szDllPath);
				}
			}
			else
			{
				TERROR("%s: CreateModInstance is not found!\n", szDllPath);
				FreeLibrary(hModule);
			}
		}
	}

	for (auto it = m_LoadedMods.Begin(); it != m_LoadedMods.End(); it++)
	{
		it->OnAllModsLoaded();
	}

	m_bLoaded = TTRUE;
}

void AModLoader::UnloadMods()
{
	return;
	for (auto it = m_LoadedMods.Begin(); it != m_LoadedMods.End(); it++)
	{
		it->OnUnload();
	}

	m_LoadedMods.RemoveAll();
}

void AModLoader::OnRenderInterfaceReady()
{
	for (auto it = m_LoadedMods.Begin(); it != m_LoadedMods.End(); it++)
	{
		// TODO: replace with the actual interface
		it->OnRenderInterfaceReady(NULL);
	}
}

void AModLoader::OnAppRendererReady()
{
	for (auto it = m_LoadedMods.Begin(); it != m_LoadedMods.End(); it++)
	{
		it->OnAppRendererReady();
	}
}

Toshi::TDList<AModInstance> &AModLoader::GetMods()
{
	return m_LoadedMods;
}
