#pragma once

#include "TDebug.h"
#include "TVector3.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TVector4
{
public:
	void Set(const TVector3 &a_rVec3)
	{
	}

	TFLOAT const &operator()(TUINT a_iIndex) const
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
	TFLOAT m_fW; // 0xC
};

TOSHI_NAMESPACE_END
