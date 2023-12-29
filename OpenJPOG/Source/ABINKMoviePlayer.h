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

	virtual TBOOL InitializeMoviePlayer();

	virtual TBOOL ShutdownMoviePlayer();

	virtual TBOOL Update(TFLOAT a_fDeltaTime);

	virtual TBOOL RenderToTexture(TTextureResource *a_pTexture);

	virtual TBOOL RenderToFrameBuffer();
	virtual TBOOL RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iSourceHeigth, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY);

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
	TBOOL RenderToTiles();

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
	TBOOL m_bDrawingFrame;        // 0x213
	TBOOL m_bRenderingTiles;      // 0x214
	HBINK m_hBink;                // 0x218
	TINT m_iFrameCount;           // 0x220
	TINT m_iFrameBufferWidth;     // 0x224
	TINT m_iFrameBufferHeight;    // 0x228
	TINT m_iWidth;                // 0x22C
	TINT m_iHeight;               // 0x230
	TPBYTE m_pFrameBufferBits;    // 0x234
	LPDIRECTSOUND m_pDirectSound; // 0x278
};

TOSHI_NAMESPACE_END