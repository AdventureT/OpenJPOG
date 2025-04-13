#include "ARootStateController.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootStateController, TTask);

ARootStateController::ARootStateController()
{
	s_pCurrentStateController = this;
	m_pBaseAppState = TNULL;
}

TBOOL ARootStateController::OnCreate()
{
	m_pBaseAppState = new ARootState();
	m_pBaseAppState->OnInsertion();
	m_pBaseAppState->OnActivate();
	return TTRUE;
}

TBOOL ARootStateController::OnUpdate(TFLOAT a_fDeltaTime)
{
	if (m_pBaseAppState) {
		ARootState& currentState = m_pBaseAppState->GetCurrent();
		currentState.OnUpdate(a_fDeltaTime);
	}
	return TTRUE;
}

void ARootStateController::OnDestroy()
{
}

void ARootStateController::TransferControl(ARootState* a_pState)
{
	GetBaseAppState()->GetCurrent().TransferControl(a_pState);
}

void ARootStateController::SetupToolBarHUD()
{
}
