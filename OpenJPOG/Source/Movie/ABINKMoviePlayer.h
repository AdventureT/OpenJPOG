#pragma once

#include "AMoviePlayer.h"
#include <dsound.h>
#include "BINK.H"
#include "RAD.H"
#include <windows.h>
#include "TKernel/TMemory.h"
#include "TRender/TTextureFactory.h"
#include "TSpriteShader/Include/TSpriteShader.h"

#define MAX_TILES 6

TOSHI_NAMESPACE_BEGIN

class ABINKMoviePlayer : public AMoviePlayer
{
	struct Rect
	{
		TTextureResource *pTexture  = TNULL; // 0x280
		TSpriteMaterial  *pMaterial = TNULL; // 0x284
		TFLOAT            m_iPosX;           // 0x288
		TFLOAT            m_iPosY;           // 0x28C
		TFLOAT            m_iWidth;          // 0x290
		TFLOAT            m_iHeight;         // 0x294
		Toshi::TVector2   m_vPos;
		Toshi::TVector2   m_vUV;

		//~Rect();

		//TBOOL Create(int a_iPosX, int a_iPosY, int a_iWidth, int a_iHeight, TFLOAT a_iRenderPos1X, TFLOAT a_iRenderPos1Y, TFLOAT a_iRenderWidth, TFLOAT a_iRenderHeight, Toshi::TTEXTURERESOURCEFORMAT a_eFormat);
	};

public:
	ABINKMoviePlayer();

	virtual TBOOL InitializeMoviePlayer();

	virtual TBOOL ShutdownMoviePlayer();

	virtual TBOOL StartMovie(TPCHAR a_szMovieName, TBOOL a_bUnk1, TPCHAR a_szUnk2, TBOOL a_bUseLocale);

	virtual TBOOL Update(TFLOAT a_fDeltaTime);

	virtual TBOOL RenderToTexture(TTextureResource *a_pTexture);

	virtual TBOOL Render();
	virtual TBOOL RenderToFrameBuffer();
	virtual TBOOL RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iSourceHeigth, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY);

	virtual TBOOL InitializeVideoResource();
	virtual TBOOL InitializeAudioResource();

	virtual TBOOL FreeVideoResource();

	// $JPOG: FUNCTION 006d6610
	virtual TBOOL IsMoviePlaying()
	{
		return !m_bHasMovieStopped;
	}

	// $JPOG: FUNCTION 006d6640
	virtual TBOOL FreeAudioResource()
	{
		delete m_pDirectSound;
		return TTRUE;
	}
	virtual void              SetLocaleInfoA(TPCHAR a_szBuffer);
	// $JPOG: FUNCTION 006d6580
	virtual TTextureResource *GetTexture() { return m_pTextures[m_iCurrentTextureIndex]; }

	void              BinkSleep(TINT a_iMicroseconds);
	TBOOL             RenderToTiles();
	// $JPOG: FUNCTION 006d6570
	TTextureResource *GetCurrentTexture() { return m_pTextures[m_iCurrentTextureIndex]; }
	// $JPOG: FUNCTION 006d6540
	void              SetCurrentTexture(TTextureResource *a_pTexture)
	{
		if (!m_pTextures[m_iCurrentTextureIndex]) {
			m_pTextures[m_iCurrentTextureIndex] = a_pTexture;
		}
	}

private:
	// $JPOG: FUNCTION 006d6520
	static void PTR4 *RADLINK RADMEMALLOC(U32 bytes)
	{
		return tmalloc(bytes, TNULL, -1);
	}

	// $JPOG: FUNCTION 006d6510
	static void RADLINK RADMEMFREE(void PTR4 *ptr)
	{
		tfree(ptr);
	}

private:
	TCHAR                    m_szMovieFileName[256]; // 0x10
	TCHAR                    m_szMovieName[256];     // 0x110
	TBOOL                    m_bHasMovieStopped;     // 0x210
	TBOOL                    m_bIsBINKInitialized;   // 0x211
	TBOOL                    m_bDrawingFrame;        // 0x213
	TBOOL                    m_bRenderingTiles;      // 0x214
	TBOOL                    m_bFrameReady;          // 0x212
	HBINK                    m_hBink;                // 0x218
	TINT                     m_iFrameCount;          // 0x220
	TINT                     m_iFrameBufferWidth;    // 0x224
	TINT                     m_iFrameBufferHeight;   // 0x228
	TINT                     m_iWidth;               // 0x22C
	TINT                     m_iHeight;              // 0x230
	Toshi::TTextureResource *m_pTextures[8];         // 0x240
	TPBYTE                   m_pFrameBufferBits;     // 0x234
	Toshi::TSpriteMaterial  *m_pMaterial;            // 0x260
	LPDIRECTSOUND            m_pDirectSound;         // 0x278
	TINT                     m_iCurrentTextureIndex; // 0x27C
	Rect                     m_aRects[6];            // 0x280
};

TOSHI_NAMESPACE_END
