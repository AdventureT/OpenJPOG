#include "pch.h"
#include "AHooks.h"
#include "ModLoader.h"
#include "HookHelpers.h"
#include "AModLoader.h"

#include "JPOGSDK/SDKHooks.h"

#include <TKernel/TKernelInterface.h>
#include <TApplication/TApplication.h>

#include <cstdio>
#include <windows.h>

//---------------------------------------------------------------------------------------------------------
// NOTE: MUST BE BUILT IN "FINAL" MODE, AS THE GAME'S TKERNELINTERFACE.DLL DOES NOT HAVE LOGGING ENABLED!!!
// Possible fix is to use different logging for it at the moment
//---------------------------------------------------------------------------------------------------------

MEMBER_HOOK(Interface::TApplication + 0x1260, Toshi::TApplication, TApplication_Create, TBOOL, const TCHAR *a_pchName, TINT a_iArgc, TCHAR **a_ppArgv)
{
	// Create the modloader task
	//AGlobalModLoaderTask::CreateSingleton()->Create();
	TDPRINTF("[ModCore] The application starts...\n");

	return CallOriginal(a_pchName, a_iArgc, a_ppArgv);
}

MEMBER_HOOK(Interface::TApplication + 0x13b0, Toshi::TApplication, TApplication_OnDestroy, TBOOL)
{
	TDPRINTF("[ModCore] The application is destroying...\n");

	return CallOriginal();
}

// Not used at the moment
// DWORD WINAPI MainThread( HMODULE hModule )
// {
// 	TDPRINTF("JPOGModCore thread has been started!\n");
//
// 	return TTRUE;
// }

static BOOL WINAPI exit_handler(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
		case CTRL_C_EVENT:
			return TRUE;
		case CTRL_BREAK_EVENT:
			return TRUE;
		case CTRL_CLOSE_EVENT:
			return TRUE;
		default:
			return FALSE;
	}

	return TRUE;
}

Toshi::TKernelInterface *g_pKernelInterface;
DWORD APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH: {
			// Generate crash dumps
			extern LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS *apExceptionInfo);
			SetUnhandledExceptionFilter(unhandled_handler);

			// Create kernel interface
			g_pKernelInterface = new Toshi::TKernelInterface(0, NULL, TTRUE);

			AllocConsole();
			FILE *fDummy;
			freopen_s(&fDummy, "CONOUT$", "w", stdout);

			// Initialise hooks
			AHooks::Initialise();
			InstallHook<TApplication_Create>();
			InstallHook<TApplication_OnDestroy>();

			SetConsoleCtrlHandler(exit_handler, TRUE);

			// Create thread
			//			TDPRINTF("Starting JPOGModCore thread...\n");

			// 			HANDLE hThread = CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0 );
			//
			// 			if ( hThread == NULL )
			// 			{
			// 				TERROR( "Couldn't start the main thread\n" );
			// 				return TFALSE;
			// 			}
			//
			// 			CloseHandle( hThread );
			return TTRUE;
		}
		default:
			return TFALSE;
	}
}
