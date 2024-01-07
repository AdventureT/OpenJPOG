#include "ABINKMoviePlayer.h"
#include "main.h"
#include "TKernel/TManagedPointer.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_USING

static U32 s_iPlayForegroundFast = 0;

ABINKMoviePlayer::ABINKMoviePlayer()
{
    m_bHasMovieStopped = TTRUE;
    m_bIsBINKInitialized = TFALSE;
    m_hBink = NULL;
    m_iFrameBufferHeight = 0;
    m_iFrameBufferWidth = 0;
    m_pFrameBufferBits = TNULL;
    RADSetMemory(RADMEMALLOC, RADMEMFREE);
    m_pTextures[0] = TNULL;
    m_pTextures[1] = TNULL;
    m_pTextures[2] = TNULL;
    m_pTextures[3] = TNULL;
    m_pTextures[4] = TNULL;
    m_pTextures[5] = TNULL;
    m_pTextures[6] = TNULL;
    m_pTextures[7] = TNULL;
    m_iCurrentTextureIndex = 0;
    SetFrameReady(TFALSE);
}

TBOOL ABINKMoviePlayer::InitializeMoviePlayer()
{
    if (!m_bIsBINKInitialized) {
        InitializeAudioResource();
        InitializeVideoResource();
        m_bIsBINKInitialized = TTRUE;
    }
    return TFALSE;
}

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

TBOOL ABINKMoviePlayer::StartMovie(TPCHAR a_szMovieName, TBOOL a_bUnk1, TPCHAR a_szUnk2, TBOOL a_bUseLocale)
{
    TRenderInterface* renderer = g_oTheApp.GetRootTask()->GetRenderInterface();

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
    m_iWidth = m_hBink->Width;
    m_iHeight = m_hBink->Height;

    TTextureResource* pTexture = GetCurrentTexture();
    if (!pTexture) {
        TTextureFactory* pTextureFactory = (TTextureFactory*)renderer->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY);
        TPVOID pData = tmalloc(0x200000, TNULL, -1);
        TSystem::MemSet(pData, 0xFF, 0x200000);
        pTexture = pTextureFactory->CreateEx(pData, 0x200000, 1024, 512, 1, TTEXTURERESOURCEFORMAT::R8G8B8A8, 32);
        if (pTexture) {
            pTexture->Validate();
            m_iFrameBufferWidth = 1024;
            m_iFrameBufferHeight = 512;
            SetCurrentTexture(pTexture);
        }
        tfree(pData);
    }

    if (!m_bDoAudio) {
        BinkSetSoundOnOff(m_hBink, 0);
    }
    RenderMovie(TTRUE);
    m_bHasMovieStopped = TFALSE;
    return TTRUE;

    return TBOOL();
}

TBOOL ABINKMoviePlayer::Update(TFLOAT a_fDeltaTime)
{
    if (!m_bHasMovieStopped && m_hBink) {
        BinkService(m_hBink);
        if (BinkWait(m_hBink)) {
            BinkSleep(500);
            return TFALSE;
        }
        RenderToFrameBuffer();
    }
    return TFALSE;
}

TBOOL ABINKMoviePlayer::RenderToTexture(TTextureResource* a_pTexture)
{
    if (m_hBink) {
        m_iWidth = m_hBink->Width;
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

TBOOL ABINKMoviePlayer::InitializeVideoResource()
{
    TRenderInterface* renderer = g_oTheApp.GetRootTask()->GetRenderInterface();
    TTextureFactory* factory = (TTextureFactory*)renderer->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY);
    TINT size;
    TTEXTURERESOURCEFORMAT textureFormat;
    TINT textureFormatSize;
    if (renderer->Supports32BitTextures()) {
        size = 4;
        textureFormat = TTEXTURERESOURCEFORMAT::R8G8B8A8;
        textureFormatSize = 32;
    }
    else {
        size = 2;
        textureFormat = TTEXTURERESOURCEFORMAT::R5G5B5A1;
        textureFormatSize = 8;
    }
    size *= 0x10000;
    TPVOID buffer = tmalloc(size, TNULL, -1);
    TSystem::MemSet(buffer, 0xFF, size);
    factory->CreateEx(buffer, size, 256, 256, 1, textureFormat, textureFormatSize);
    return TTRUE;
}

TBOOL ABINKMoviePlayer::InitializeAudioResource()
{
    TRenderD3DInterface* renderer = (TRenderD3DInterface*)g_oTheApp.GetRootTask()->GetRenderInterface();
    HRESULT hResult = DirectSoundCreate(NULL, &m_pDirectSound, NULL);

    if (FAILED(hResult)) {
        m_pDirectSound = NULL;
    }
    else {
        m_pDirectSound->SetCooperativeLevel(renderer->GetMSWindow()->GetHWND(), 2);
        BinkSoundUseDirectSound(m_pDirectSound);
    }
    return TTRUE;
}

TBOOL ABINKMoviePlayer::FreeVideoResource()
{
    return TTRUE;
}

void ABINKMoviePlayer::SetLocaleInfoA(TPCHAR a_szBuffer)
{
    //Toshi::TSystem::GetCStringPool();
    //Toshi::TSystem::GetLocale();
    sprintf(a_szBuffer, "Data\\Movies\\%s.bik", m_szMovieFileName);
}

void ABINKMoviePlayer::BinkSleep(TINT a_iMicroseconds)
{
    static S32 s_iTotalSleep = 0;
    static S32 s_iSleepForward = 0;
    static U64 s_iFrequency = 1000;
    static S32 s_bFrequencyAquired = 0;

    if (!s_bFrequencyAquired)
    {
        s_bFrequencyAquired = 1;
        QueryPerformanceFrequency((LARGE_INTEGER*)&s_iFrequency);
    }

    s_iTotalSleep += a_iMicroseconds;

    if ((s_iTotalSleep - s_iSleepForward) > 1000)
    {
        U64 start, end;
        s_iTotalSleep -= s_iSleepForward;

        QueryPerformanceCounter((LARGE_INTEGER*)&start);
        Sleep(s_iTotalSleep / 1000);
        QueryPerformanceCounter((LARGE_INTEGER*)&end);

        end = ((end - start) * (U64)1000000) / s_iFrequency;

        s_iSleepForward = (U32)end - s_iTotalSleep;
        s_iTotalSleep %= 1000;
    }
}

TBOOL ABINKMoviePlayer::RenderToTiles()
{
    return TBOOL();
}
