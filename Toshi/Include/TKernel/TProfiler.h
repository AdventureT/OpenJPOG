#pragma once

#include "TDebug.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TProfiler
{
public:
	void Start();
	void Stop();

	static void TOSHI_API PrintSummary();

private:
	inline static TBOOL m_sProfilerStopped = TTRUE;

	LARGE_INTEGER m_iStartTime;
};

TOSHI_NAMESPACE_END
