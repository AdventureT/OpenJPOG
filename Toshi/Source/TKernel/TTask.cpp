#include "TTask.h"
#include "TScheduler.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TTask, TObject);

TBOOL TTask::Create()
{
	TASSERT(IsCreated()==TFALSE);
	if (!IsCreated()) {
		if (!OnCreate()) {
			OnDestroy();
			m_Tree->Remove(this, TFALSE);
			Delete();

			return TFALSE;
		}

		m_iState |= State_Created;
		Activate(TTRUE);
	}

	return TTRUE;
}

TBOOL TTask::CreateFailed()
{
	TASSERT(IsCreated() == TFALSE);

	if (!IsCreated()) {
		m_Tree->Remove(this, TFALSE);
		Delete();
	}

	return TFALSE;
}

void TTask::Activate(TBOOL a_bActivate)
{
	TUINT8 oldState = m_iState;
	TUINT8 newFlags = a_bActivate ? State_Active : 0;
	m_iState = (m_iState & ~State_Active) | newFlags;

	if (oldState != m_iState) {
		if (a_bActivate) {
			OnActivate();
		}
		else {
			OnDeactivate();
		}
	}
}

void TTask::DestroyTask()
{
	m_pScheduler->DestroyTask(*this);
}

TScheduler* TTask::GetScheduler()
{
	return m_pScheduler;
}
