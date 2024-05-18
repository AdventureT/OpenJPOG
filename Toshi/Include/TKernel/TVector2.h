#pragma once

#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TVector2
{
public:

	TVector2()
	{
		
	}

	TVector2(TFLOAT a_fX, TFLOAT a_fY)
	{
		Set(a_fX, a_fY);
	}

	TVector2(const TFLOAT a_pfVec[2])
	{
		Set(a_pfVec);
	}

	void Set(TFLOAT a_fX, TFLOAT a_fY)
	{
		m_fX = a_fX;
		m_fY = a_fY;
	}

	void Set(const TFLOAT a_pfVec[2])
	{
		m_fX = a_pfVec[0];
		m_fY = a_pfVec[1];
	}

	static const TVector2 VEC_ZERO;
	static const TVector2 VEC_POSX;
	static const TVector2 VEC_POSY;
	static const TVector2 VEC_NEGX;
	static const TVector2 VEC_NEGY;
private:
	TFLOAT m_fX; // 0x0
	TFLOAT m_fY; // 0x4
};

TOSHI_NAMESPACE_END