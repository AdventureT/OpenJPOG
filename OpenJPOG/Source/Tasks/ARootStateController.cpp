#include "ARootStateController.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootStateController, TTask);

ARootStateController::ARootStateController()
{
	s_pCurrentStateController = this;
	m_pBaseAppState = TNULL;
}

void ARootStateController::TransferController(ARootState* a_pState)
{
}
