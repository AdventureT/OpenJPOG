#pragma once

#include "TKernel/TDebug.h"
#include "TKernel/TVector2.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class AMoviePlayer
{
public:
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

	virtual TBOOL InitializeMoviePlayer()
	{
		if (!m_bIsInitialized) {
			m_bIsInitialized = TTRUE;
		}
		return TFALSE;
	}

	virtual TBOOL ShutdownMoviePlayer()
	{
		if (m_bIsInitialized) {
			m_bIsInitialized = TFALSE;
		}
		return TFALSE;
	}

	virtual TBOOL Update(TFLOAT a_fDeltaTime)
	{
		return TFALSE;
	}

	virtual TBOOL StartMovie(TPCHAR a_szMovieName, TBOOL a_bUnk1, TPCHAR a_szUnk2, TBOOL a_bUseLocale)
	{
		return TFALSE;
	}

	virtual TBOOL CloseMovie()
	{
		return TFALSE;
	}

	virtual TBOOL StopMovie()
	{
		m_bIsStopped = TTRUE;
		return TFALSE;
	}

	virtual TBOOL PauseMovie(TBOOL a_bPause)
	{
		m_bIsStopped = TTRUE;
		return TFALSE;
	}

	virtual TBOOL IsMoviePlaying()
	{
		return !m_bIsStopped;
	}

	virtual TBOOL IsPaused()
	{
		return m_bIsPaused;
	}

	virtual TBOOL RenderToFrameBuffer()
	{
		return TFALSE;
	}

	virtual TBOOL IsInitialized()
	{
		return m_bIsInitialized;
	}

	virtual void SetLocaleInfoA(TPCHAR a_szLocale)
	{
	}

	virtual TBOOL FrameReady()
	{
		return m_bIsFrameReady;
	}

	virtual void RenderMovie(TBOOL a_bRender)
	{
		m_bRenderMovie = a_bRender;
	}

	virtual TBOOL Render()
	{
		return TFALSE;
	}
	// $JPOG: FUNCTION 006d73d0
	virtual TBOOL Render_BackBufferBlit()
	{
		return TFALSE;
	}

	virtual void SetDoAudio(TBOOL a_bDoAudio)
	{
		m_bDoAudio = a_bDoAudio;
	}

	virtual void SetDoVideo(TBOOL a_bDoVideo)
	{
		m_bDoVideo = a_bDoVideo;
	}

	virtual void SetFullScreen(TBOOL a_bFullscreen)
	{
		m_bIsFullscreen = a_bFullscreen;
	}

	virtual void SetFrameReady(TBOOL a_bFreameReady)
	{
		m_bIsFrameReady = a_bFreameReady;
	}

private:
	virtual TBOOL GetTextureUVs(TVector2 &a_rvUV1, TVector2 &a_rvUV2)
	{
		return TFALSE;
	}

	virtual TBOOL IsFullscreen()
	{
		return m_bIsFullscreen;
	}

	virtual TBOOL RenderToTexture(TTextureResource *a_pTextureResource)
	{
		return TFALSE;
	}

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
