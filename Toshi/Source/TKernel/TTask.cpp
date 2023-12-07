#include "TTask.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTask, TObject);

TBOOL TTask::Create()
{
	TASSERT(IsCreated()==TFALSE);
	return TBOOL();
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
