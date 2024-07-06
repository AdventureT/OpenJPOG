#include "TKernelInterface.h"
#include <windows.h>
#include <direct.h> // _getcwd
#include <TKernel/TFile.h>
#include TOSHI_MULTIPLATFORM(TNativeFile)
#include "TUser.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TKernelInterface, TObject);

static TUINT s_iFlagUser = 0;
static TKernelInterface* s_pKernel;

TKernelInterface::TKernelInterface(TINT argc, TPCHAR* const argv, TBOOL a_bVerbose)
{
	TWARNING("TKernelInterface::TKernelInterface() not implemented\n");
	m_pScheduler = TNULL;
	m_fDeltaTime = 0.0f;
	m_fAvgFPS = 0.0f;
	m_bVerbose = a_bVerbose;

	if (!HASFLAG(s_iFlagUser & 1)) {
		s_iFlagUser |= 1;
		static TUser s_oUser = TUser("Toshi");
		s_pKernel = TNULL;
		s_oUser.Register();
		// FUN_1003213a WTF is that???
	}
	s_pKernel = this;

	if (m_bVerbose) {
		TDPRINTF("Creating TKernelInterface\n");
	}

	TCHAR pPath[260];
	TPCHAR pBuffer = _getcwd(pPath, sizeof(pPath));
	TVALIDADDRESS(pBuffer);
	TFileManager *pFileManager = new TFileManager();
	TVALIDADDRESS(pFileManager);
	TNativeFileSystem *pLocalSystem = new TNativeFileSystem("local");
	TVALIDADDRESS(pLocalSystem);
	pLocalSystem->SetPrefix(pBuffer);
	TNativeFileSystem *pAbsSystem = new TNativeFileSystem("abs");
	TVALIDADDRESS(pAbsSystem);
	pAbsSystem->SetPrefix("");
	pFileManager->SetSystemPath("local");

	if (a_bVerbose) {
		DumpInfo();
	}

	m_pScheduler = new TScheduler(this);
}

TBOOL TKernelInterface::Update()
{
	THPTimer *pSysTimer = GetSystemTimer();
	pSysTimer->Update();
	TFLOAT deltaTime = pSysTimer->GetDelta();
	m_fDeltaTime += deltaTime;

	if (m_fDeltaTime > 1.0f) {
		m_fAvgFPS += (1.0f / deltaTime) * 0.5f;
		m_fDeltaTime = 0.0f;
	}

	m_pScheduler->Update();
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

TKernelInterfaceDLL* TKernelInterface::FindInterface(const TCString& a_rszInterface)
{
	for (auto i = m_Interfaces.Begin(); i != m_Interfaces.End(); i++) {
		if (i->GetFilename() == a_rszInterface) {
			return i;
		}
	}
	return TNULL;
}

TKernelInterfaceDLL* TKernelInterface::LoadInterface(const TCString& a_rszInterface)
{
	TKernelInterfaceDLL* pInterface = FindInterface(a_rszInterface);
	if (pInterface) {
		return pInterface;
	}
	pInterface = new TKernelInterfaceDLL();
	if (!pInterface->Load(a_rszInterface)) {
		delete pInterface;
	}
	m_Interfaces.InsertTail(*pInterface);
	return pInterface;
}

void TKernelInterface::UnloadInterface(TKernelInterfaceDLL& a_rInterface)
{
	a_rInterface.Unload();
	m_Interfaces.Delete(a_rInterface);
}

void TKernelInterface::UnloadInterface(const TCString& a_rszInterface)
{
	TKernelInterfaceDLL* pInterface = FindInterface(a_rszInterface);
	if (pInterface) {
		UnloadInterface(*pInterface);
	}
}
