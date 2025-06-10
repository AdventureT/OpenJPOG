#pragma once

#include "TKernel/TTask.h"
#include "States/ARootState.h"

class ARootStateController;

static inline ARootStateController *s_pCurrentStateController = TNULL;

class ARootStateController : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootStateController);

public:
	ARootStateController();

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;
	virtual void  OnDestroy() override;

	void TransferControl(ARootState *a_pState);
	void SetupToolBarHUD();

public:
	// $JPOG: FUNCTION 0046dfe0
	ARootState                            *GetBaseAppState() { return m_pBaseAppState; }
	// $JPOG: FUNCTION 0046dfc0
	static ARootStateController *TOSHI_API GetRootStateController() { return s_pCurrentStateController; }
	// $JPOG: FUNCTION 0058ec80
	ARootState &GetCurrentGameState()
	{
		return m_pBaseAppState->GetCurrent();
	}

private:
	ARootState *m_pBaseAppState; // 0x24
};
