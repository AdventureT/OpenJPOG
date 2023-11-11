#include "TDebug.h"
#include <stdio.h>
#include <windows.h>
#include "TSystem.h"

#ifdef TOSHI_DEBUG

TOSHI_NAMESPACE_BEGIN

void __stdcall TDebug_VPrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs)
{
	if ((a_uiFlags & FLAG_UNK3) == 0) {
		if ((a_uiFlags & FLAG_UNK1) == 0) {
			if ((a_uiFlags & FLAG_UNK2) == 0) {
				TDebug::PrintIndent();
			}
			else {
				TDebug::s_iLogIndent--;
				TDebug::PrintIndent();
				TDebug::DebugFilePrintString(const_cast<TPCHAR>("} "));
			}
		}
		else {
			TDebug::PrintIndent();
			TDebug::DebugFilePrintString(const_cast<TPCHAR>("{ "));
			TDebug::s_iLogIndent++;
		}
	}
	TPCHAR pcString = (TPCHAR)TSystem::GetScratchMem();
	vsprintf(pcString, a_pcFormat, a_vargs);
	TDebug::DebugFilePrintString(pcString);
}

void __stdcall TDebug_VPrintf(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs)
{
	TDebug_VPrintfDirect(a_uiFlags, a_pcFormat, a_vargs);
}

void __cdecl TDebug_Printf(TPCCHAR a_pcFormat, ...)
{
	va_list args;
	va_start(args, a_pcFormat);
	TDebug_VPrintf(FLAG_UNK, a_pcFormat, args);
	va_end(args);
}

static TCHAR idk[30]{};
static TPCHAR s_pcExpression = TNULL;
static TPCHAR s_pcFile       = TNULL;
static TINT   s_iLine        = -1;

TBOOL __stdcall TDebug::AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, TBOOL& a_bUnk)
{
	TPCCHAR str = a_bUnk ? "(IGNORED)" : idk;
	TDebug_Printf("TASSERT \"%s\" failed: file \"%s\", line %d %s\n", a_pcExpression, a_pcFile, a_iLine, str);
	if (a_bUnk) return TFALSE;
	s_pcExpression = a_pcExpression;
	s_pcFile = a_pcFile;
	s_iLine = a_iLine;
	HWND hWnd = GetActiveWindow();
	if (hWnd) hWnd = GetLastActivePopup(hWnd);
	//DialogBoxParamA(GetModuleHandleA("TKernelInterface"), )
	return TTRUE;
}

void __stdcall TDebug::PrintIndent()
{
	TINT i;
	for (i = s_iLogIndent * 2; i >= 16; i-=16) {
		DebugFilePrintString(s_sSixteenSpace);
	}
	if (i > 0) {
		DebugFilePrintString(&s_sSixteenSpace[16-i]);
	}
}

void __stdcall TDebug::DebugFilePrintString(TPCHAR a_pcString)
{
	if (m_pDebugFile && m_bEnableDebugFile) {

	}
	else {
		printf("%s", a_pcString);
	}
}

TOSHI_NAMESPACE_END

#endif

