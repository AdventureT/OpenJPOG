#pragma once

#include "AFrontEndState.h"

class AFrontEndSplashState : public AFrontendState
{
	DECLARE_DYNAMIC(AFrontEndSplashState)

public:

	virtual void OnActivate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;

private:
	static inline Toshi::TCString* sm_asLogoScreens = TNULL;
};

