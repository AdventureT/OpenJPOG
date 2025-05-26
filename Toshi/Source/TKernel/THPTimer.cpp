#include "THPTimer.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 10017540
THPTimer::THPTimer()
{
	LARGE_INTEGER iPerformancCounter;
	if (!QueryPerformanceCounter(&iPerformancCounter)) {
		TASSERT(!"QueryPerformanceCounter is not supported on this processor!");
	}
	Reset();
}

// $TKernelInterface: FUNCTION 10017650
void THPTimer::Reset()
{
	QueryPerformanceCounter(&m_iCurrentTime);
	QueryPerformanceFrequency(&m_iFrequency);
	m_iOldTime = m_iCurrentTime;
	m_fDelta   = 0;
}

// $TKernelInterface: FUNCTION 10017590
void THPTimer::Update()
{
	m_iOldTime = m_iCurrentTime;
	QueryPerformanceCounter(&m_iCurrentTime);

	TCFLOAT ratio = 1.0f / m_iFrequency.QuadPart;
	m_fDelta      = (m_iCurrentTime.QuadPart - m_iOldTime.QuadPart) * ratio;
	m_fCurrent    = m_iCurrentTime.QuadPart * ratio;
}

// $TKernelInterface: FUNCTION 10017610
TUINT THPTimer::GetRaw32()
{
	LARGE_INTEGER raw32;
	QueryPerformanceCounter(&raw32);
	return raw32.LowPart;
}

// $TKernelInterface: FUNCTION 100175f0
TUINT64 THPTimer::GetRaw64()
{
	LARGE_INTEGER raw32;
	QueryPerformanceCounter(&raw32);
	return raw32.QuadPart;
}
