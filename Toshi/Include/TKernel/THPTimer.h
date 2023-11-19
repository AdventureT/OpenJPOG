#pragma once
#include "TDebug.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT THPTimer
{
public:
	THPTimer();

	void Reset();
	void Update();

	TUINT GetRaw32();
	TUINT64 GetRaw64();
	float GetDelta() { return m_fDelta; }
	float GetCurrent() { return m_fCurrent; }

private:
	LARGE_INTEGER m_iFrequency;        // 0x0
	TFLOAT m_fCurrent;                 // 0x8
	LARGE_INTEGER m_iOldTime;          // 0x10
	LARGE_INTEGER m_iCurrentTime;      // 0x18
	TFLOAT m_fDelta;                   // 0x20
};

TOSHI_NAMESPACE_END
