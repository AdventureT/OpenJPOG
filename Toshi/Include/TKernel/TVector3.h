#pragma once

#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TVector3
{
public:
	TVector3()
	{

	}
	// $TKernelInterface: FUNCTION 10009820
	TVector3(TFLOAT a_fX, TFLOAT a_fY, TFLOAT a_fZ)
	{
		Set(a_fX, a_fY, a_fZ);
	}
	// $TKernelInterface: FUNCTION 100096e0
	void Set(TFLOAT a_fX, TFLOAT a_fY, TFLOAT a_fZ)
	{
		m_fX = a_fX;
		m_fY = a_fY;
		m_fZ = a_fZ;
	}

	const TFLOAT &operator()(TUINT a_iIndex) const
	{
		return (&m_fX)[a_iIndex];
	}

	TFLOAT &operator()(TUINT a_iIndex)
	{
		return (&m_fX)[a_iIndex];
	}

private:
	TFLOAT m_fX; // 0x0
	TFLOAT m_fY; // 0x4
	TFLOAT m_fZ; // 0x8
};

TOSHI_NAMESPACE_END
