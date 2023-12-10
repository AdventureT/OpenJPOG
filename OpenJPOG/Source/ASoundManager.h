#pragma once
#include "TKernel/TDebug.h"
#include "fmod.h"

TOSHI_NAMESPACE_BEGIN

class ASoundManager
{
public:
	TFLOAT GetPitch(TINT a_iChannel) const;
};

TOSHI_NAMESPACE_END