#include "AFrontEndSplashState.h"
#include "GUI/AGUISystem.h"
#include "main.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AFrontEndSplashState, ARootState)

void AFrontEndSplashState::OnActivate()
{
	ARootState::OnActivate();
	AMoviePlayer* pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();
	pMoviePlayer->SetDoAudio(TTRUE);
	pMoviePlayer->InitializeMoviePlayer();
}

TBOOL AFrontEndSplashState::OnUpdate(TFLOAT a_fDeltaTime)
{
	static TBOOL s_StartMovie = TTRUE;

	AMoviePlayer* pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();

	if (s_StartMovie) {
		s_StartMovie = TFALSE;
		if (pMoviePlayer && !pMoviePlayer->IsMoviePlaying()) {
			pMoviePlayer->StartMovie((TPCHAR)"Intro", TFALSE, (TPCHAR)"Intro", TTRUE);
		}
	}

	return TBOOL();
}
