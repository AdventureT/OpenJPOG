#include "ABINKMoviePlayer.h"
#include "main.h"
#include "TKernel/TManagedPointer.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

static U32 s_iPlayForegroundFast = 0;

// $JPOG: FUNCTION 006d52d0
ABINKMoviePlayer::ABINKMoviePlayer()
{
	m_bHasMovieStopped   = TTRUE;
	m_bIsBINKInitialized = TFALSE;
	m_hBink              = NULL;
	m_iFrameBufferHeight = 0;
	m_iFrameBufferWidth  = 0;
	m_pFrameBufferBits   = TNULL;
	RADSetMemory(RADMEMALLOC, RADMEMFREE);
	m_pTextures[0]         = TNULL;
	m_pTextures[1]         = TNULL;
	m_pTextures[2]         = TNULL;
	m_pTextures[3]         = TNULL;
	m_pTextures[4]         = TNULL;
	m_pTextures[5]         = TNULL;
	m_pTextures[6]         = TNULL;
	m_pTextures[7]         = TNULL;
	m_iCurrentTextureIndex = 0;
	SetFrameReady(TFALSE);
}

// $JPOG: FUNCTION 006d5370
TBOOL ABINKMoviePlayer::InitializeMoviePlayer()
{
	if (!m_bIsBINKInitialized) {
		InitializeAudioResource();
		InitializeVideoResource();
		m_bIsBINKInitialized = TTRUE;
	}
	return TFALSE;
}

// $JPOG: FUNCTION 006d57b0
TBOOL ABINKMoviePlayer::ShutdownMoviePlayer()
{
	if (m_bIsBINKInitialized) {
		FreeAudioResource();
		FreeVideoResource();
		m_bIsBINKInitialized = TFALSE;
		SetFrameReady(TFALSE);
	}
	return TFALSE;
}

// $JPOG: FUNCTION 006d58b0
TBOOL ABINKMoviePlayer::StartMovie(TPCHAR a_szMovieName, TBOOL a_bUnk1, TPCHAR a_szUnk2, TBOOL a_bUseLocale)
{
	TRenderInterface *renderer = g_oTheApp.GetRootTask()->GetRenderInterface();

	if (a_szMovieName) {
		Toshi::TSystem::StringCopy(m_szMovieFileName, a_szMovieName, -1);
	}
	else {
		Toshi::TSystem::MemSet(m_szMovieFileName, 0, sizeof(m_szMovieFileName));
	}

	if (a_szUnk2) {
		Toshi::TSystem::StringCopy(m_szMovieName, a_szUnk2, -1);
	}
	else {
		Toshi::TSystem::MemSet(m_szMovieName, 0, sizeof(m_szMovieName));
	}

	TCHAR buffer3[256];
	if (a_bUseLocale) {
		SetLocaleInfoA(buffer3);
	}
	else {
		sprintf(buffer3, "Data\\Movies\\%s.bik", m_szMovieFileName);
	}

	m_bDrawingFrame = TTRUE;
	SetFrameReady(TFALSE);
	m_iFrameCount = 0;

	if (m_bDoAudio) {
		m_hBink = BinkOpen(buffer3, 0);
	}
	else {
		BinkSetSoundTrack(0, NULL);
		m_hBink = BinkOpen(buffer3, BINKSNDTRACK);
	}
	if (!m_hBink) {
		return TFALSE;
	}

	InitializeMoviePlayer();
	m_iWidth  = m_hBink->Width;
	m_iHeight = m_hBink->Height;

	TTextureResource *pTexture = GetCurrentTexture();
	if (!pTexture) {
		TTextureFactory *pTextureFactory = (TTextureFactory *)renderer->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY);
		TPCHAR           pData           = new char[0x200000];
		TSystem::MemSet(pData, 0xFF, sizeof(pData));
		pTexture = pTextureFactory->CreateEx(pData, 0x200000, 1024, 512, 1, TTEXTURERESOURCEFORMAT_R8G8B8A8, 32);
		if (pTexture) {
			pTexture->Validate();
			m_iFrameBufferWidth  = 1024;
			m_iFrameBufferHeight = 512;
			SetCurrentTexture(pTexture);
		}
		delete[] pData;
	}

	if (!m_bDoAudio) {
		BinkSetSoundOnOff(m_hBink, 0);
	}
	RenderMovie(TTRUE);
	m_bHasMovieStopped = TFALSE;
	return TTRUE;
}

// $JPOG: FUNCTION 006d5840
TBOOL ABINKMoviePlayer::Update(TFLOAT a_fDeltaTime)
{
	if (!m_bHasMovieStopped && m_hBink) {
		m_bRenderingTiles = TFALSE;
		BinkService(m_hBink);
		if (BinkWait(m_hBink)) {
			m_bDrawingFrame = TFALSE;
			BinkSleep(500);
			return TFALSE;
		}
		m_bDrawingFrame = TTRUE;
		RenderToFrameBuffer();
	}
	return TFALSE;
}

// $JPOG: FUNCTION 006d6190
TBOOL ABINKMoviePlayer::Render()
{
	if (!m_bRenderMovie) {
		return TFALSE;
	}
	if (!FrameReady()) {
		return TFALSE;
	}
	TSpriteShader *pShader = AGUISystem::GetGUISystem()->GetShader();
	for (int i = 0; i < MAX_TILES; i++) {
	}
}

// $JPOG: FUNCTION 006d5dc0
TBOOL ABINKMoviePlayer::RenderToTexture(TTextureResource *a_pTexture)
{
	if (m_hBink) {
		m_iWidth  = m_hBink->Width;
		m_iHeight = m_hBink->Height;
		if (a_pTexture && !m_bHasMovieStopped) {
			if (s_iPlayForegroundFast) {
				BinkDoFrame(m_hBink);
				BinkNextFrame(m_hBink);
				return FALSE;
			}
			m_iFrameCount++;
			// TODO: Do some Texture stuff
			BinkDoFrame(m_hBink);
			if (m_iFrameCount == m_hBink->Frames) {
			}
		}
	}
	return TBOOL();
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer()
{
	if (!m_bHasMovieStopped && !m_bRenderingTiles) {
		RenderToTiles();
		m_bRenderingTiles = TTRUE;
	}
	return TFALSE;
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iDestWidth, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY)
{
	BinkCopyToBufferRect(m_hBink, a_pDest, a_iDestPitch, a_iDestHeigth,
	                     a_iDestX, a_iDestY, a_iSrcX, a_iSrcY, m_hBink->Width, m_hBink->Height, BINKCOPYALL | BINKNOSKIP | BINKSURFACE32A);
	TPBYTE pBuf = a_pDest + a_iDestX + a_iDestY * a_iDestWidth;

	if (a_iDestHeigth == a_iDestWidth) {
		// I think this ignores alpha?
		for (TINT i = 0; i < a_iDestHeigth; i++) {
			for (TINT j = 0; j < a_iDestWidth; j++) {
				*pBuf = *pBuf | 0xFF000000;
			}
			pBuf += a_iDestPitch * 4;
		}
	}
	else if (a_iDestHeigth != a_iDestWidth && a_iDestHeigth - a_iDestWidth >= 0) {
		// I think this ignores alpha?
		for (TINT i = 0; i < a_iDestWidth; i++) {
			for (TINT j = 0; j < a_iDestWidth; j++) {
				*pBuf = *pBuf | 0xFF000000;
			}
			pBuf += a_iDestPitch * 4;
		}
	}

	return TFALSE;
}


// $JPOG: FUNCTION 006d53a0
TBOOL ABINKMoviePlayer::InitializeVideoResource()
{
	TRenderInterface      *renderer = g_oTheApp.GetRootTask()->GetRenderInterface();
	TTextureFactory       *factory  = (TTextureFactory *)renderer->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY);
	TINT                   size;
	TTEXTURERESOURCEFORMAT textureFormat;
	TINT                   textureFormatSize;
	if (renderer->Supports32BitTextures()) {
		size              = 4;
		textureFormat     = TTEXTURERESOURCEFORMAT_R8G8B8A8;
		textureFormatSize = 32;
	}
	else {
		size              = 2;
		textureFormat     = TTEXTURERESOURCEFORMAT_R5G5B5A1;
		textureFormatSize = 8;
	}
	size *= 256 * 256;
	TPVOID buffer = tmalloc(size);
	TSystem::MemSet(buffer, 0xFF, size);
	TSpriteShader *pShader = AGUISystem::GetGUISystem()->GetShader();
	for (int i = 0; i < MAX_TILES; i++)
	{
		m_pTextures[i] = factory->CreateEx(buffer, size, 256, 256, 1, textureFormat, textureFormatSize);
		m_pTextures[i]->SetAddressModeMode(TTextureResource::ADDRESSMODE_CLAMP);
		m_pTextures[i]->Validate();
		
		m_pMaterial = pShader->CreateMaterial(TNULL);
		m_pMaterial->Create();
		m_pMaterial->SetBlendMode(6);
		m_pMaterial->Validate();

		m_aRects[i].pTexture = m_pTextures[i];
		m_aRects[i].pMaterial = m_pMaterial;
	}
	m_aRects[0].m_iPosX   = 0.0f;
	m_aRects[0].m_iPosY   = 0.0f;
	m_aRects[0].m_iWidth  = 256.0f;
	m_aRects[0].m_iHeight = 256.0f;
	m_aRects[0].m_vPos.Set(0.0f, 0.0f);
	m_aRects[0].m_vUV.Set(1.0f, 1.0f);

	m_aRects[1].m_iPosX   = 256.0f;
	m_aRects[1].m_iPosY   = 0.0f;
	m_aRects[1].m_iWidth  = 512.0f;
	m_aRects[1].m_iHeight = 256.0f;
	m_aRects[1].m_vPos.Set(0.0f, 0.0f);
	m_aRects[1].m_vUV.Set(1.0f, 1.0f);

	m_aRects[2].m_iPosX   = 512.0f;
	m_aRects[2].m_iPosY   = 0.0f;
	m_aRects[2].m_iWidth  = 640.0f;
	m_aRects[2].m_iHeight = 256.0f;
	m_aRects[2].m_vPos.Set(0.0f, 0.0f);
	m_aRects[2].m_vUV.Set(0.5f, 1.0f);

	m_aRects[3].m_iPosX   = 0.0f;
	m_aRects[3].m_iPosY   = 256.0f;
	m_aRects[3].m_iWidth  = 256.0f;
	m_aRects[3].m_iHeight = 448.0f;
	m_aRects[3].m_vPos.Set(0.0f, 0.0f);
	m_aRects[3].m_vUV.Set(1.0f, 0.75f);

	m_aRects[4].m_iPosX   = 256.0f;
	m_aRects[4].m_iPosY   = 256.0f;
	m_aRects[4].m_iWidth  = 512.0f;
	m_aRects[4].m_iHeight = 448.0f;
	m_aRects[4].m_vPos.Set(0.0f, 0.0f);
	m_aRects[4].m_vUV.Set(1.0f, 0.75f);

	m_aRects[5].m_iPosX   = 512.0f;
	m_aRects[5].m_iPosY   = 256.0f;
	m_aRects[5].m_iWidth  = 640.0f;
	m_aRects[5].m_iHeight = 448.0f;
	m_aRects[5].m_vPos.Set(0.0f, 0.0f);
	m_aRects[5].m_vUV.Set(0.5f, 0.75f);

	return TTRUE;
}

// $JPOG: FUNCTION 006d5710
TBOOL ABINKMoviePlayer::InitializeAudioResource()
{
	TRenderD3DInterface *renderer = g_oTheApp.GetRootTask()->GetRenderInterface();
	HRESULT              hResult  = DirectSoundCreate(NULL, &m_pDirectSound, NULL);

	if (FAILED(hResult)) {
		m_pDirectSound = NULL;
	}
	else {
		m_pDirectSound->SetCooperativeLevel(renderer->GetMSWindow()->GetHWND(), 2);
		BinkSoundUseDirectSound(m_pDirectSound);
	}
	return TTRUE;
}

// $JPOG: FUNCTION 006d57f0
TBOOL ABINKMoviePlayer::FreeVideoResource()
{
	return TTRUE;
}

// $JPOG: FUNCTION 006d6400
void ABINKMoviePlayer::SetLocaleInfoA(TPCHAR a_szBuffer)
{
	//Toshi::TSystem::GetCStringPool();
	//Toshi::TSystem::GetLocale();
	sprintf(a_szBuffer, "Data\\Movies\\%s.bik", m_szMovieFileName);
}

// $JPOG: FUNCTION 006d6310
void ABINKMoviePlayer::BinkSleep(TINT a_iMicroseconds)
{
	static S32 s_iTotalSleep       = 0;
	static S32 s_iSleepForward     = 0;
	static U64 s_iFrequency        = 1000;
	static S32 s_bFrequencyAquired = 0;

	if (!s_bFrequencyAquired) {
		s_bFrequencyAquired = 1;
		QueryPerformanceFrequency((LARGE_INTEGER *)&s_iFrequency);
	}

	s_iTotalSleep += a_iMicroseconds;

	if ((s_iTotalSleep - s_iSleepForward) > 1000) {
		U64 start, end;
		s_iTotalSleep -= s_iSleepForward;

		QueryPerformanceCounter((LARGE_INTEGER *)&start);
		Sleep(s_iTotalSleep / 1000);
		QueryPerformanceCounter((LARGE_INTEGER *)&end);

		end = ((end - start) * (U64)1000000) / s_iFrequency;

		s_iSleepForward = (U32)end - s_iTotalSleep;
		s_iTotalSleep %= 1000;
	}
}

// $JPOG: FUNCTION 006d5f20
TBOOL ABINKMoviePlayer::RenderToTiles()
{
	if (m_hBink == TNULL || m_bHasMovieStopped || !m_bDrawingFrame) {
		return TFALSE;
	}

	auto pRootTask        = g_oTheApp.GetRootTask();
	auto pRenderInterface = pRootTask->GetRenderInterface();

	m_iFrameCount++;

	pRenderInterface->Supports32BitTextures();

	BinkDoFrame(m_hBink);

	if (!m_bUnk && m_iFrameCount == m_hBink->Frames) {
		StopMovie();
		m_bHasMovieStopped = TTRUE;
		return TFALSE;
	}

	SetFrameReady(TTRUE);
	m_bFrameReady = TTRUE;

	// Render to each tile
	for (int i = 0; i < MAX_TILES; i++)
	{
		TTextureResourceHAL *pTexture = static_cast<TTextureResourceHAL *>(m_aRects[i].pTexture);
		IDirect3DTexture8 *d3dtexture = pTexture->GetD3DTexture();

		D3DLOCKED_RECT lockedRect;
		d3dtexture->LockRect(0, &lockedRect, NULL, 0);

		BinkCopyToBuffer(
			m_hBink,
			lockedRect.pBits,
			lockedRect.Pitch,
			0x100,
			static_cast<int>(m_aRects[i].m_iWidth - m_aRects[i].m_iPosX),
			static_cast<int>(m_aRects[i].m_iHeight - m_aRects[i].m_iPosY),
			BINKSURFACE8P);

		d3dtexture->UnlockRect(0);
	}

	m_bFrameReady = TTRUE;
	BinkNextFrame(m_hBink);

	return TTRUE;
}
