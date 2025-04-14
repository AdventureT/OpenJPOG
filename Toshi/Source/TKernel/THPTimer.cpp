#include "THPTimer.h"

TOSHI_NAMESPACE_USING

THPTimer::THPTimer()
{
	LARGE_INTEGER iPerformancCounter;
	if (!QueryPerformanceCounter(&iPerformancCounter)) {
		TASSERT(!"QueryPerformanceCounter is not supported on this processor!");
	}
	Reset();
}

void THPTimer::Reset()
{
	QueryPerformanceCounter(&m_iCurrentTime);
	QueryPerformanceFrequency(&m_iFrequency);
	m_iOldTime = m_iCurrentTime;
	m_fDelta   = 0;
}

void THPTimer::Update()
{
	m_iOldTime = m_iCurrentTime;
	QueryPerformanceCounter(&m_iCurrentTime);

	TCFLOAT ratio = 1.0f / m_iFrequency.QuadPart;
	m_fDelta      = (m_iCurrentTime.QuadPart - m_iOldTime.QuadPart) * ratio;
	m_fCurrent    = m_iCurrentTime.QuadPart * ratio;
}

TUINT THPTimer::GetRaw32()
{
	LARGE_INTEGER raw32;
	QueryPerformanceCounter(&raw32);
	return raw32.LowPart;
}

TUINT64 THPTimer::GetRaw64()
{
	LARGE_INTEGER raw32;
	QueryPerformanceCounter(&raw32);
	return raw32.QuadPart;
}
