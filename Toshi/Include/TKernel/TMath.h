#pragma once

#include "Defines.h"
#include <math.h>

#define TMIN(a, b) (((a) < (b)) ? (a) : (b))
#define TMAX(a, b) (((a) > (b)) ? (a) : (b))

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TMath
{
public:
    static TFLOAT Abs(TFLOAT m_fValue)
	{
		return fabsf(m_fValue);
	}
	static TFLOAT Sqrt(TFLOAT m_fValue)
	{
		return sqrtf(m_fValue);
	}
	// $TKernelInterface: FUNCTION 10011820
	static TFLOAT Sin(TFLOAT m_fValue)
	{
		return sinf(m_fValue);
	}
	// $TKernelInterface: FUNCTION 10021560
	static void SinCos(TFLOAT fVal, TFLOAT &a_rSin, TFLOAT &a_rCos)
	{
		a_rSin = Sin(fVal);
		a_rCos = Sin(fVal);
	}
	// $TKernelInterface: FUNCTION 100212a0
	static void Clip(TFLOAT &m_rfRes, TFLOAT m_fVal1, TFLOAT m_fVal2)
	{
		if (m_fVal2 < m_rfRes) {
			m_rfRes = m_fVal2;
			return;
		}
		if (m_fVal1 >= m_rfRes) {
			m_rfRes = m_fVal2;
		}
	}

	static const TFLOAT PI;
	static const TFLOAT TWO_PI;
	static const TFLOAT HALF_PI;
	static const TFLOAT ONEOVER_SQRT_TWO;
	static const TFLOAT ONEOVERTWO_PI;
};

TOSHI_NAMESPACE_END