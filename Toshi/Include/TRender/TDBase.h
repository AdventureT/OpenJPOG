#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TDBase
{
public:
	class TRENDERINTERFACE_EXPORTS TKeyFrame
	{
	public:
		void Get(TFLOAT &a_rTime);
	};

	TFLOAT GetTransDeviation() { return s_fDeltaTransDeviation; }
	TFLOAT GetTransEpsilon() { return s_fDeltaTransEpsilon; }

	TFLOAT SetTransDeviation(TFLOAT a_fDeltaTransDeviation) { s_fDeltaTransDeviation = a_fDeltaTransDeviation; }
	TFLOAT SetTransEpsilon(TFLOAT a_fDeltaTransEpsilon) { s_fDeltaTransEpsilon = a_fDeltaTransEpsilon; }

	static inline TFLOAT s_fDeltaTransDeviation = 0.05f;
	static inline TFLOAT s_fDeltaTransEpsilon   = 0.05f / 5.0f;
};

TOSHI_NAMESPACE_END
