#pragma once

#include "AFrontEndState.h"

class AFrontEndSplashState : public AFrontendState
{
	DECLARE_DYNAMIC(AFrontEndSplashState)

public:
	// $JPOG: FUNCTION 004899d0
	AFrontEndSplashState()
		: AFrontEndSplashState(TTRUE, 0.0f)
	{
	}

	AFrontEndSplashState(TBOOL a_bUnk, TFLOAT a_fUnk);

	virtual void  OnActivate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;
	// $JPOG: FUNCTION 0048a220
	virtual void OnInsertion() override;

private:
	TBOOL RunLogoState(TFLOAT a_fDeltaTime);

private:
	static inline Toshi::TCString *sm_asLogoScreens    = new Toshi::TCString("bkg_bink.tml");
	static inline TBOOL            s_bLoadedSound      = TFALSE;
	static inline TFLOAT           sm_fLogoDisplayTime = 2.5f;

	TFLOAT m_fMoviePlayingTime; // 0x54
	TBOOL  m_bMovieStarted;     // 0x5C
	TBOOL  m_bInitialise;       // 0x64
	TINT   m_iLogoScreenIndex;  // 0x68
	TFLOAT m_fLogoDisplayTime;  // 0x6C
	TBOOL  m_bLogoScreenSet;    // 0x70
};
