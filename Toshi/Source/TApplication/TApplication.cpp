#include "TApplication.h"

TOSHI_NAMESPACE_USING

TBOOL TApplication::Create(TPCCHAR a_pcName, TINT argc, TPCCHAR* argv)
{
	m_pcName = a_pcName;
	if (m_bVerbose)
	{
		TDPRINTF("Creating Toshi Application \"%s\".\n", m_pcName.GetString());
		if (argc > 0 && argv)
		{
			TDPRINTF("Command line parameters: %d.\n", argc);
			for (TINT i = 0; i < argc; i++)
			{
				TDPRINTF("  Arg[%d]: \"%s\"\n", i, argv[i+1]);
			}
		}
	}
	m_pKernel = new TKernelInterface(a_pcName, argc, argv, m_bVerbose);
	return TTRUE;
}

TBOOL TApplication::Execute()
{
	TASSERT(TTRUE==TApplication::IsCreated());
	return TBOOL();
}
