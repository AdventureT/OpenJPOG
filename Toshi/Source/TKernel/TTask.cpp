#include "TTask.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTask, TObject);

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

		//auto oldState = m_State;
		//m_State |= State_Created;
		//Activate(TTRUE);
	}

	return TTRUE;
}

TBOOL TTask::CreateFailed()
{
	return TBOOL();
}

TBOOL TTask::OnCreate()
{
	return TBOOL();
}

TBOOL TTask::OnUpdate(TFLOAT a_fDeltaTime)
{
	return TBOOL();
}

void TTask::OnDestroy()
{
}

TBOOL TTask::OnChildDying(TTask* child)
{
	return TBOOL();
}

void TTask::OnChildDied(TClass* a_pClass, TTask* a_pDeletedTask)
{
}

void TTask::OnActivate()
{
}

void TTask::OnDeactivate()
{
}
