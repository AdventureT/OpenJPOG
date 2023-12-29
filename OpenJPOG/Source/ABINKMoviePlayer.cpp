#include "ABINKMoviePlayer.h"

TOSHI_NAMESPACE_USING

ABINKMoviePlayer::ABINKMoviePlayer()
{
    m_bHasMovieStopped = TTRUE;
    m_bIsBINKInitialized = TFALSE;
    m_hBink = NULL;
    m_iFrameBufferHeight = 0;
    m_iFrameBufferWidth = 0;
    m_pFrameBufferBits = TNULL;
    RADSetMemory(RADMEMALLOC, RADMEMFREE);
    SetFrameReady(TFALSE);
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer()
{
    return TBOOL();
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iUnk, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY)
{
    if (a_iDestHeigth == a_iUnk) {
        BinkCopyToBufferRect(m_hBink, a_pDest, a_iDestPitch, a_iDestHeigth,
            a_iDestX, a_iDestY, a_iSrcX, a_iSrcY, m_hBink->Width, m_hBink->Height, BINKCOPYALL | BINKNOSKIP | BINKSURFACE32A);
    }
    return TBOOL();
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
