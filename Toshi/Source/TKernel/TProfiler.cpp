#include "TProfiler.h"

TOSHI_NAMESPACE_USING

void TProfiler::Start()
{
	m_sProfilerStopped = TFALSE;
	QueryPerformanceCounter(&m_iStartTime);
}

void TProfiler::Stop()
{
	m_sProfilerStopped = TTRUE;

}

void TProfiler::PrintSummary()
{
}
