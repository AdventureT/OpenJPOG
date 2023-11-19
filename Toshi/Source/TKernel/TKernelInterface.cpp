#include "TKernelInterface.h"
#include <windows.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TKernelInterface, TObject);

TKernelInterface::TKernelInterface(TINT argc, TPCHAR* const argv, TBOOL a_bVerbose)
{
	TWARNING("TKernelInterface::TKernelInterface() not implemented");
}

TBOOL TKernelInterface::Update()
{
	TWARNING("TKernelInterface::Update() not implemented");
	return TTRUE;
}

static int GetProcessorSpeed()
{
	LARGE_INTEGER qwFreq, qwStart, qwStop;
	BOOL bSuccess = QueryPerformanceFrequency(&qwFreq);
	if (bSuccess == FALSE) return 0;
	QueryPerformanceCounter(&qwStart);
	unsigned __int64 Start = __rdtsc();
	Sleep(10);
	QueryPerformanceCounter(&qwStop);
	return ((__rdtsc() - Start) * qwFreq.LowPart) / (qwStop.LowPart - qwStart.HighPart);
}

void TKernelInterface::DumpInfo()
{
	TDPRINTF("> Toshi system info:\n");
	OSVERSIONINFOEX osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	TBOOL bSuccess = GetVersionExA((LPOSVERSIONINFO)&osvi);

	if (!bSuccess)
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		bSuccess = GetVersionExA((LPOSVERSIONINFO)&osvi);
		if (!bSuccess) goto skipPlatform;
	}
	TPCCHAR system;
	if (osvi.dwPlatformId == 2) system = "Microsoft Windows NT";
	else if (osvi.dwPlatformId == 1) {
		if (osvi.dwMajorVersion < 5 && (osvi.dwMajorVersion != 4 || osvi.dwMinorVersion == 0)) {
			system = "Microsoft Windows 95";
		}
		else {
			system = "Microsoft Windows 98";
		}
	}
	else if (osvi.dwPlatformId == 0) {
		system = "Microsoft Win32s";
	}
	if (!bSuccess) {
		TDPRINTF("Windows version: %s version %d.%d (Build %d)\n", system, osvi.dwMajorVersion,
			osvi.dwMinorVersion, osvi.dwBuildNumber);
	}
	else {
		TDPRINTF("Windows version: %s version %d.%d (Build %d) Service Pack %d.%d\n", system, osvi.dwMajorVersion,
			osvi.dwMinorVersion, osvi.dwBuildNumber,
			osvi.wServicePackMajor, osvi.wServicePackMinor);
	}

skipPlatform:
	TCHAR pcComputerName[16];
	DWORD size = sizeof(pcComputerName);
	if (GetComputerName(pcComputerName, &size)) {
		TDPRINTF("Computer name: \"%s\"\n", pcComputerName);
	}

	TCHAR pcUserName[256];
	size = sizeof(pcUserName);
	if (GetUserName(pcUserName, &size)) {
		TDPRINTF("User name: \"%s\"\n", pcUserName);
	}
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	TDPRINTF("Number of processors: %d\n", sysInfo.dwNumberOfProcessors);
	TDPRINTF("CPU Speed: %dMHZ\n", GetProcessorSpeed());
	MEMORYSTATUS memStatus;
	memStatus.dwLength = sizeof(memStatus);
	GlobalMemoryStatus(&memStatus);
	TDPRINTF("Total physical memory: %uKB\n", memStatus.dwTotalPhys >> 16);
	TDPRINTF("Available physical memory: %uKB\n", memStatus.dwAvailPhys >> 16);
	TDPRINTF("<\n");
}
