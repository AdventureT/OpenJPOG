#include "ARootStateController.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootStateController, TTask);

// $JPOG: FUNCTION 0058e780
ARootStateController::ARootStateController()
{
	s_pCurrentStateController = this;
	m_pBaseAppState           = TNULL;
}

// $JPOG: FUNCTION 0058e7b0
TBOOL ARootStateController::OnCreate()
{
	m_pBaseAppState = new ARootState();
	m_pBaseAppState->OnInsertion();
	m_pBaseAppState->OnActivate();
	return TTRUE;
}

// $JPOG: FUNCTION 0058e840
TBOOL ARootStateController::OnUpdate(TFLOAT a_fDeltaTime)
{
	if (m_pBaseAppState) {
		ARootState &currentState = m_pBaseAppState->GetCurrent();
		currentState.OnUpdate(a_fDeltaTime);
	}
	return TTRUE;
}

// $JPOG: FUNCTION 0058e800
void ARootStateController::OnDestroy()
{
}

// $JPOG: FUNCTION 0058ec50
void ARootStateController::TransferControl(ARootState *a_pState)
{
	GetBaseAppState()->GetCurrent().TransferControl(a_pState);
}

// $JPOG: FUNCTION 0058ea90
void ARootStateController::SetupToolBarHUD()
{
}
