#include "TTask.h"
#include "TScheduler.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTask, TObject);

TBOOL TTask::Create()
{
	TASSERT(IsCreated() == TFALSE);
	if (!IsCreated()) {
		if (!OnCreate()) {
			OnDestroy();
			m_Tree->Remove(this, TFALSE);
			Delete();

			return TFALSE;
		}

		m_Flags |= State_Created;
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
	TUINT8 oldState = m_Flags;
	TUINT8 newFlags = a_bActivate ? State_Active : 0;
	m_Flags         = (m_Flags & ~State_Active) | newFlags;

	if (oldState != m_Flags) {
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

TScheduler *TTask::GetScheduler()
{
	return m_pScheduler;
}
