#pragma once
#include "TVector3.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TSphere
{
private:
	TVector3 m_Origin;
	TFLOAT m_fRadius;
};

TOSHI_NAMESPACE_END