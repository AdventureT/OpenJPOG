#include "TApplication.h"
#include "TCString.h"

TOSHI_NAMESPACE_USING

HWND GetConsoleHandle()
{
	HWND     hwnd;
	TCHAR    pszWindowTitle[512];
	TCHAR    time[24];
	TCString szWindowTitle("{1B5D8052-529A-4c88-9DDE-EE523D440B00}");
	_ultoa(timeGetTime(), time, 16);
	szWindowTitle += time;

	if (GetConsoleTitle(pszWindowTitle, sizeof(pszWindowTitle)) == FALSE) return NULL;
	SetConsoleTitle(szWindowTitle);
	hwnd = FindWindow(NULL, szWindowTitle);
	SetConsoleTitle(pszWindowTitle);
	return hwnd;
}

TApplication::TApplication()
{
	m_pKernel      = TNULL;
	m_uiState      = 0;
	m_bVerbose     = TTRUE;
	m_bShowConsole = TTRUE;
	m_hConsole     = new HWND();
	*m_hConsole    = GetConsoleHandle();
}

TApplication::~TApplication()
{
#ifdef TOSHI_NOTFINAL
	if (m_bVerbose) {
		TDPRINTF("Destroying Toshi Application \"%s\".\n", m_pcName.GetString());
	}
#endif
}

TBOOL TApplication::Create(TPCCHAR a_pcName, TINT argc, TPCHAR *const argv)
{
	m_pcName = a_pcName;
#ifdef TOSHI_NOTFINAL
	if (m_bVerbose)
	{
		TDPRINTF("Creating Toshi Application \"%s\".\n", m_pcName.GetString());
		if (argc > 0 && argv)
		{
			TDPRINTF("Command line parameters: %d.\n", argc);
			for (TINT i = 0; i < argc; i++)
			{
				TDPRINTF("  Arg[%d]: \"%s\"\n", i, argv[i + 1]);
			}
		}
	}
#endif
	m_pKernel = new TKernelInterface(argc, argv, m_bVerbose);
	return OnCreate(argc, argv);
}

TBOOL TApplication::Execute()
{
	TASSERT(TTRUE == TApplication::IsCreated());
	while (m_pKernel->Update())
	{
		if (!OnUpdate(m_pKernel->GetSystemTimer()->GetDelta()) || HASFLAG(m_uiState & TApplicationFlag_Destroyed)) break;
	}
	return OnDestroy();
}

TBOOL TApplication::ShowConsole(TBOOL a_bShowConsole)
{
	ShowWindow(*m_hConsole, a_bShowConsole);
	UpdateWindow(*m_hConsole);
	TBOOL show     = m_bShowConsole;
	m_bShowConsole = a_bShowConsole;
	return show;
}
