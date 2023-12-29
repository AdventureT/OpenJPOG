#pragma once

#include "AMoviePlayer.h"
#include <dsound.h>
#include "BINK.H"
#include "RAD.H"
#include <windows.h>
#include "TKernel/TMemory.h"

TOSHI_NAMESPACE_BEGIN

class ABINKMoviePlayer : public AMoviePlayer
{
public:
	ABINKMoviePlayer();

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
		if (m_bIsBINKInitialized) {
			FreeAudioResource();
			FreeVideoResource();
			m_bIsBINKInitialized = TFALSE;
			SetFrameReady(TFALSE);
		}
		return TFALSE;
	}

	virtual TBOOL Update(TFLOAT a_fDeltaTime)
	{
		
		if (m_bIsBINKInitialized && m_hBink) {
			BinkService(m_hBink);
			if (BinkWait(m_hBink) != 0) {
				BinkSleep(500);
				return TFALSE;
			}
			RenderToFrameBuffer();
		}
		return TFALSE;
	}

	virtual TBOOL RenderToFrameBuffer();
	virtual TBOOL RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iUnk, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY);

	virtual TBOOL FreeVideoResource()
	{
		return TTRUE;
	}

	virtual TBOOL FreeAudioResource()
	{
		delete m_pDirectSound;
		return TTRUE;
	}

	void BinkSleep(TINT a_iMicroseconds);

private:

	static void PTR4* RADLINK RADMEMALLOC(U32 bytes)
	{
		return tmalloc(bytes, TNULL, -1);
	}

	static void RADLINK RADMEMFREE(void PTR4* ptr)
	{
		tfree(ptr);
	}

private:
	TBOOL m_bHasMovieStopped;     // 0x210
	TBOOL m_bIsBINKInitialized;   // 0x211
	HBINK m_hBink;                // 0x218
	TINT m_iFrameBufferWidth;     // 0x224
	TINT m_iFrameBufferHeight;    // 0x228
	TPBYTE m_pFrameBufferBits;    // 0x234
	LPDIRECTSOUND m_pDirectSound; // 0x278
};

TOSHI_NAMESPACE_END