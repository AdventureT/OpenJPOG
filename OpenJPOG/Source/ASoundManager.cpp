#include "ASoundManager.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ASoundManager, TObject);

// $JPOG: FUNCTION 0068e1f0
TFLOAT ASoundManager::GetPitch(TINT a_iChannel) const
{
	TINT freq;
	if (a_iChannel != -1) {
		FSOUND_SAMPLE *pSample = FSOUND_GetCurrentSample(a_iChannel);
		if (pSample) {
			FSOUND_Sample_GetDefaults(pSample, &freq, NULL, NULL, NULL);
			return (TFLOAT)FSOUND_GetFrequency(a_iChannel) / freq;
		}
	}
	return 0.0f;
}
