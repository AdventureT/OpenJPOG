#include "TDebug.h"
#include <stdio.h>
#include <windows.h>
#include "TSystemTools.h"

#ifdef TOSHI_NOTFINAL

#  include "../resource.h"

TOSHI_NAMESPACE_BEGIN

void TOSHI_API TDebug_VPrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs)
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

void TOSHI_API TDebug_VPrintf(TUINT a_uiFlags, TPCCHAR a_pcFormat, va_list a_vargs)
{
	TDebug_VPrintfDirect(a_uiFlags, a_pcFormat, a_vargs);
}

void TOSHI_CALLBACKAPI TDebug_Printf(TPCCHAR a_pcFormat, ...)
{
	va_list args;
	va_start(args, a_pcFormat);
	TDebug_VPrintf(FLAG_UNK, a_pcFormat, args);
	va_end(args);
}

void TOSHI_CALLBACKAPI TDebug_Printf(TUINT a_uiFlags, TPCCHAR a_pcFormat, ...)
{
	va_list args;
	va_start(args, a_pcFormat);
	TDebug_VPrintf(a_uiFlags, a_pcFormat, args);
	va_end(args);
}

void TOSHI_CALLBACKAPI TDebug_PrintfDirect(TPCCHAR a_pcFormat, ...)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED | FOREGROUND_GREEN);
	}
	TDebug_VPrintfDirect(0, a_pcFormat, TNULL);
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
}

void TOSHI_CALLBACKAPI TDebug_PrintfDirect(TUINT a_uiFlags, TPCCHAR a_pcFormat, ...)
{
	va_list vargs;
	va_start(vargs, a_pcFormat);
	TDebug_VPrintf(a_uiFlags, a_pcFormat, vargs);
	va_end(vargs);
}

void TOSHI_CALLBACKAPI TDebug_CPrintf(TINT a_iFlags, TPCCHAR a_pcFormat, ...)
{
	if (a_iFlags != 0) {
		va_list vargs;
		va_start(vargs, a_pcFormat);
		TDebug_VPrintf(FLAG_UNK, a_pcFormat, vargs);
		va_end(vargs);
	}
}

void TOSHI_CALLBACKAPI TDebug_Message(TDebug::MSGLEVEL a_eMsgLevel, TPCCHAR a_pcFormat, ...)
{
	if (TDebug::s_iMessageLevel <= a_eMsgLevel) {
		va_list vargs;
		va_start(vargs, a_pcFormat);
		vprintf(a_pcFormat, vargs);
		va_end(vargs);
	}
}

void TOSHI_CALLBACKAPI TDebug_PrintError(TPCCHAR a_pcFormat, ...)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	}
	TDebug_VPrintfDirect(0, "[Toshi Error]:", TNULL);
	va_list vargs;
	va_start(vargs, a_pcFormat);
	TDebug_VPrintfDirect(FLAG_UNK3, a_pcFormat, vargs);
	va_end(vargs);
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
}

void TOSHI_CALLBACKAPI TDebug_PrintWarning(TPCCHAR a_pcFormat, ...)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_GREEN);
	}
	TDebug_VPrintfDirect(0, "[Toshi Warning]:", TNULL);
	va_list vargs;
	va_start(vargs, a_pcFormat);
	TDebug_VPrintfDirect(FLAG_UNK3, a_pcFormat, vargs);
	va_end(vargs);
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput != INVALID_HANDLE_VALUE) {
		SetConsoleTextAttribute(hConsoleOutput, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	}
}

static TPCCHAR g_szAssertIgnored = "";
static TPCCHAR g_szAssertFilename;
static TINT    g_uiAssertLineNumber;
static TPCCHAR g_szAssertExpression;

INT_PTR CALLBACK AssertionDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_INITDIALOG: {
			if (!g_szAssertFilename)
				g_szAssertFilename = "***INVALID***";

			if (!g_szAssertExpression)
				g_szAssertExpression = "***INVALID***";

			SetDlgItemTextA(hwnd, IDC_FILE, g_szAssertFilename);
			SetDlgItemInt(hwnd, IDC_LINE, g_uiAssertLineNumber, TRUE);
			SetDlgItemTextA(hwnd, IDC_EXPRESSION, g_szAssertExpression);
			return TRUE;
		}
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_QUIT:      // Quit
				case IDC_DEBUG:     // Debug
				case IDC_IGNORE:    // Ignore
				case IDC_IGNOREALL: // IgnoreAll
					EndDialog(hwnd, wParam);
					break;
			}
			break;
		default:
			return FALSE;
	}

	return TRUE;
}


TBOOL TDebug::AssertHandler(TPCHAR a_pcExpression, TPCHAR a_pcFile, TINT a_iLine, TBOOL &a_bIgnoreAll)
{
	TPCCHAR str = a_bIgnoreAll ? "(IGNORED)" : g_szAssertIgnored;
	TDebug_Printf("TASSERT \"%s\" failed: file \"%s\", line %d %s\n", a_pcExpression, a_pcFile, a_iLine, str);
	if (a_bIgnoreAll) return TFALSE;
	g_szAssertExpression = a_pcExpression;
	g_szAssertFilename   = a_pcFile;
	g_uiAssertLineNumber = a_iLine;
	HWND hWnd            = GetActiveWindow();
	if (hWnd) hWnd = GetLastActivePopup(hWnd);
	INT_PTR res          = DialogBoxParamA(GetModuleHandleA("TKernelInterface"), MAKEINTRESOURCE(IDD_ASSERT), hWnd, AssertionDlgProc, 0);
	g_szAssertExpression = TNULL;
	g_szAssertFilename   = TNULL;
	g_uiAssertLineNumber = -1;
	TBOOL bRes           = TTRUE;
	if (res != -1)
	{
		switch (LOWORD(res))
		{
			case IDC_QUIT: // Quit
				ExitProcess(1);
				break;
			case IDC_DEBUG: // Debug
				bRes = TTRUE;
				break;
			case IDC_IGNORE: // Ignore
				bRes = TFALSE;
				break;
			case IDC_IGNOREALL: // Ignore All
				bRes         = TFALSE;
				a_bIgnoreAll = TTRUE;
				break;
		}
	}
	return bRes;
}

void TOSHI_API TDebug::PrintIndent()
{
	TINT i;
	for (i = s_iLogIndent * 2; i >= 16; i -= 16) {
		DebugFilePrintString(s_sSixteenSpace);
	}
	if (i > 0) {
		DebugFilePrintString(&s_sSixteenSpace[16 - i]);
	}
}

void TOSHI_API TDebug::DebugFilePrintString(TPCHAR a_pcString)
{
	if (m_pDebugFile && m_bEnableDebugFile) {
	}
	else {
		printf("%s", a_pcString);
	}
}

TOSHI_NAMESPACE_END

#else

TOSHI_NAMESPACE_BEGIN

void TOSHI_CALLBACKAPI TDebug_Message(TDebug::MSGLEVEL a_eMsgLevel, TPCCHAR a_pcFormat, ...)
{
	if (TDebug::s_iMessageLevel <= a_eMsgLevel) {
		va_list vargs;
		va_start(vargs, a_pcFormat);
		vprintf(a_pcFormat, vargs);
		va_end(vargs);
	}
}

void TOSHI_API TDebug::DebugFilePrintString(TPCHAR a_pcString)
{
	if (m_pDebugFile && m_bEnableDebugFile) {
	}
	else {
		printf("%s", a_pcString);
	}
}

TOSHI_NAMESPACE_END

#endif
