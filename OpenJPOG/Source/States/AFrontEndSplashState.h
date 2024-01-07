#pragma once

#include "AFrontEndState.h"

class AFrontEndSplashState : public AFrontendState
{
	DECLARE_DYNAMIC(AFrontEndSplashState)

public:

	AFrontEndSplashState() : AFrontEndSplashState(TTRUE, 0.0f)
	{
		
	}

	AFrontEndSplashState(TBOOL a_bUnk, TFLOAT a_fUnk);

	virtual void OnActivate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;

private:
	static inline Toshi::TCString* sm_asLogoScreens = TNULL;
};

