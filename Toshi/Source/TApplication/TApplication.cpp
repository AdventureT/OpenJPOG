#include "TApplication.h"
#include "TDebug.h"

TOSHI_NAMESPACE_USING

TBOOL TApplication::Create(TPCCHAR a_pcName, TINT argc, TPCCHAR* argv)
{
	m_pcName = a_pcName;
	if (m_bVerbose)
	{
		TDebug_Printf("Creating Toshi Application \"%s\".\n", m_pcName.GetString());
		if (argc > 0 && argv)
		{
			TDebug_Printf("Command line parameters: %d.\n", argc);
			for (TINT i = 0; i < argc; i++)
			{
				TDebug_Printf("  Arg[%d]: \"%s\"\n", i, argv[i+1]);
			}
		}
	}
	return TTRUE;
}