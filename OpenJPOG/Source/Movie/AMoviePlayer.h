#pragma once

#include "TKernel/TDebug.h"
#include "TKernel/TVector2.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class AMoviePlayer
{
public:
	// $JPOG: FUNCTION 006d74b0
	AMoviePlayer()
	{
		m_bIsStopped     = TTRUE;
		m_bIsInitialized = TFALSE;
		m_bIsFrameReady  = TFALSE;
		m_bIsFullscreen  = TTRUE;
		m_bIsPaused      = TFALSE;
		m_bRenderMovie   = TTRUE;
	}

	virtual ~AMoviePlayer() = default;

	// $JPOG: FUNCTION 006d7490
	virtual TBOOL InitializeMoviePlayer()
	{
		if (!m_bIsInitialized) {
			m_bIsInitialized = TTRUE;
		}
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7480
	virtual TBOOL ShutdownMoviePlayer()
	{
		if (m_bIsInitialized) {
			m_bIsInitialized = TFALSE;
		}
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7470
	virtual TBOOL Update(TFLOAT a_fDeltaTime)
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7460
	virtual TBOOL StartMovie(TPCHAR a_szMovieName, TBOOL a_bUnk1, TPCHAR a_szUnk2, TBOOL a_bUseLocale)
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7450
	virtual TBOOL CloseMovie()
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7440
	virtual TBOOL StopMovie()
	{
		m_bIsStopped = TTRUE;
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7430
	virtual TBOOL PauseMovie(TBOOL a_bPause)
	{
		m_bIsStopped = TTRUE;
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7420
	virtual TBOOL IsMoviePlaying()
	{
		return !m_bIsStopped;
	}

	// $JPOG: FUNCTION 00472910
	virtual TBOOL IsPaused()
	{
		return m_bIsPaused;
	}

	// $JPOG: FUNCTION 006d7410
	virtual TBOOL RenderToFrameBuffer()
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 00472900
	virtual TBOOL IsInitialized()
	{
		return m_bIsInitialized;
	}

	// $JPOG: FUNCTION 006d7400
	virtual void SetLocaleInfoA(TPCHAR a_szLocale)
	{
	}

	// $JPOG: FUNCTION 006d73f0
	virtual TBOOL FrameReady()
	{
		return m_bIsFrameReady;
	}

	// $JPOG: FUNCTION 004728f0
	virtual void RenderMovie(TBOOL a_bRender)
	{
		m_bRenderMovie = a_bRender;
	}

	// $JPOG: FUNCTION 006d73e0
	virtual TBOOL Render()
	{
		return TFALSE;
	}
	// $JPOG: FUNCTION 006d73d0
	virtual TBOOL Render_BackBufferBlit()
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 004728e0
	virtual void SetDoAudio(TBOOL a_bDoAudio)
	{
		m_bDoAudio = a_bDoAudio;
	}

	// $JPOG: FUNCTION 004728d0
	virtual void SetDoVideo(TBOOL a_bDoVideo)
	{
		m_bDoVideo = a_bDoVideo;
	}

	// $JPOG: FUNCTION 006d73c0
	virtual void SetFullScreen(TBOOL a_bFullscreen)
	{
		m_bIsFullscreen = a_bFullscreen;
	}

	// $JPOG: FUNCTION 004728c0
	virtual void SetFrameReady(TBOOL a_bFreameReady)
	{
		m_bIsFrameReady = a_bFreameReady;
	}

private:
	// $JPOG: FUNCTION 006d73b0
	virtual TBOOL GetTextureUVs(TVector2 &a_rvUV1, TVector2 &a_rvUV2)
	{
		return TFALSE;
	}

	virtual TBOOL IsFullscreen()
	{
		return m_bIsFullscreen;
	}

	// $JPOG: FUNCTION 006d7390
	virtual TBOOL RenderToTexture(TTextureResource *a_pTextureResource)
	{
		return TFALSE;
	}

	// $JPOG: FUNCTION 006d7380
	virtual TTextureResource *GetTexture()
	{
		return TNULL;
	}

protected:
	// 0x0 vftable
	TBOOL m_bIsStopped;     // 0x4
	TBOOL m_bIsInitialized; // 0x5
	TBOOL m_bIsFrameReady;  // 0x7
	TBOOL m_bIsFullscreen;  // 0x8
	TBOOL m_bDoAudio;       // 0x9
	TBOOL m_bDoVideo;       // 0xA
	TBOOL m_bIsPaused;      // 0xB
	TBOOL m_bRenderMovie;   // 0xC
};

TOSHI_NAMESPACE_END
