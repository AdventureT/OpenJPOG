#pragma once
#include "TKernel/TDebug.h"
#include "TKernel/TObject.h"
#include "fmod.h"

class ASample
{
};

class ASoundManager : public Toshi::TObject
{
	DECLARE_DYNAMIC(ASoundManager);

	struct AChannel
	{
	};

protected:
	inline static ASample **s_aSamples = TNULL;

public:
	TFLOAT GetPitch(TINT a_iChannel) const;
	TBOOL  GetPaused(TINT a_iChannel) const { return a_iChannel != -1 ? FSOUND_GetPaused(a_iChannel) : TFALSE; }
	TFLOAT GetPan(TINT a_iChannel) const { return a_iChannel != -1 ? -1.0f + (FSOUND_GetPan(a_iChannel) / 127.5f) : 0.0f; }
	TFLOAT GetSFXVolume() { return 1.0f; };
};
