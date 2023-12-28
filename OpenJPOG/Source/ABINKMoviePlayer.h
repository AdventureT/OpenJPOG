#pragma once

#include "AMoviePlayer.h"
#include <dsound.h>
#include "BINK.H"

TOSHI_NAMESPACE_BEGIN

class ABINKMoviePlayer : public AMoviePlayer
{
	virtual TBOOL InitializeMoviePlayer()
	{
		HRESULT hResult = DirectSoundCreate(NULL, &m_pDirectSound, NULL);
		if (FAILED(hResult)) {
			m_pDirectSound = NULL;
		} 
		else {
			BinkSoundUseDirectSound(m_pDirectSound);
		}
		return TTRUE;
	}

	virtual TBOOL ShutdownMoviePlayer()
	{
		if (m_bIsInitialized) {
			m_bIsInitialized = TFALSE;
		}
		return TFALSE;
	}

private:
	LPDIRECTSOUND m_pDirectSound;
};

TOSHI_NAMESPACE_END