#include "ASoundManager.h"

TOSHI_NAMESPACE_USING

TFLOAT ASoundManager::GetPitch(TINT a_iChannel) const
{
	TINT freq;
	if (a_iChannel != -1) {
		FSOUND_SAMPLE* pSample = FSOUND_GetCurrentSample(a_iChannel);
		if (pSample) {
			FSOUND_Sample_GetDefaults(pSample, &freq, NULL, NULL, NULL);
			return FSOUND_GetFrequency(a_iChannel) / a_iChannel;
		}
	}
	return 0.0f;
}
