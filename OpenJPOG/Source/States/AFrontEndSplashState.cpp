#include "AFrontEndSplashState.h"
#include "GUI/AGUISystem.h"
#include "main.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AFrontEndSplashState, AFrontendState)

AFrontEndSplashState::AFrontEndSplashState(TBOOL a_bInitialise, TFLOAT a_fMoviePlayingTime)
{
	m_bInitialise      = a_bInitialise;
	m_fMoviePlayingTime = a_fMoviePlayingTime;
	m_bMovieStarted    = TFALSE;
	m_iLogoScreenIndex = 0;
	m_bLogoScreenSet   = TFALSE;
}

void AFrontEndSplashState::OnActivate()
{
	ARootState::OnActivate();
	AMoviePlayer *pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();

	//AGUISystem::GetGUISystem()->Get;

	pMoviePlayer->SetDoAudio(TTRUE);
	pMoviePlayer->InitializeMoviePlayer();
}

TBOOL AFrontEndSplashState::OnUpdate(TFLOAT a_fDeltaTime)
{
	AMoviePlayer *pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();

	if (m_bInitialise) {
		static TFLOAT s_fStopLoadingSounds     = 0.0f;
		static TFLOAT s_fStartLoadingSounds    = 5.0f;
		static TFLOAT s_fTimeLeftLoadingSounds = 5.0f;
		if (s_fStopLoadingSounds < s_fTimeLeftLoadingSounds) {
			if (s_fTimeLeftLoadingSounds < s_fStartLoadingSounds && s_bLoadedSound) {
				// ASoundManager
				s_bLoadedSound = TTRUE;
			}
			s_fTimeLeftLoadingSounds -= a_fDeltaTime;
			return ARootState::OnUpdate(a_fDeltaTime);
		}
		if (!m_bLogoScreenSet) {
			m_oHUDState.ClearBackgroundPicture();
			m_oHUDState.SetBackgroundMatLib(sm_asLogoScreens[m_iLogoScreenIndex]);
			m_bLogoScreenSet = TTRUE;
		}
		if (RunLogoState(a_fDeltaTime)) {
			return ARootState::OnUpdate(a_fDeltaTime);
		}
	}

	if (!m_bMovieStarted) {
		m_bMovieStarted = TTRUE;
	}
	static TBOOL s_StartMovie = TTRUE;
	if (s_StartMovie) {
		s_StartMovie = TFALSE;
		if (pMoviePlayer && !pMoviePlayer->IsMoviePlaying()) {
			pMoviePlayer->StartMovie((TPCHAR) "Intro", TFALSE, (TPCHAR) "Intro", TTRUE);
			m_oHUDState.ClearBackgroundPicture();
		}
	}
	else if (!pMoviePlayer) {
		//SetStartScreen();
	}
	else {
		if (!pMoviePlayer->IsMoviePlaying()) {
			pMoviePlayer->RenderMovie(TFALSE);
			//SetStartScreen();
		}
		else {
			pMoviePlayer->RenderMovie(TTRUE);
		}
	}

	return ARootState::OnUpdate(a_fDeltaTime);
}

void AFrontEndSplashState::OnInsertion()
{
	AFrontendState::OnInsertion();
	if (m_bInitialise) {
		m_oHUDState.SetBackgroundMatLib("Data/Matlibs/bkg_Lic_pc.tml");
	}
}

TBOOL AFrontEndSplashState::RunLogoState(TFLOAT a_fDeltaTime)
{
	if (m_iLogoScreenIndex <= 0) {
		return TFALSE;
	}
	TFLOAT curLogoTime = m_fLogoDisplayTime + a_fDeltaTime;
	if (sm_fLogoDisplayTime <= curLogoTime) {
		m_iLogoScreenIndex++;
		m_fLogoDisplayTime = 0;
		if (m_iLogoScreenIndex <= 0) {
			return TFALSE;
		}
		m_oHUDState.ClearBackgroundPicture();
		m_oHUDState.SetBackgroundMatLib(sm_asLogoScreens[m_iLogoScreenIndex]);
	}
	else {
		m_fLogoDisplayTime = curLogoTime;
	}
	return TTRUE;
}
