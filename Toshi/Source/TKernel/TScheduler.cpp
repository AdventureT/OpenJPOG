#include "TScheduler.h"
#include "TKernelInterface.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TScheduler, TObject);

TBOOL Profiler_Control_ParentStart = TFALSE;
TBOOL Profiler_Control_ParentStop = TFALSE;
TProfiler Profiler_Program;

TScheduler::TScheduler(TKernelInterface* a_pKernel)
{
	m_pCurrentTask = TNULL;
	m_pKernel = a_pKernel;
	m_fCurrentTimeDelta = 0.0f;
	m_fTotalTime = 0.0f;
	m_fDebugSlowTime = 1.0f;
	m_iFrameCount = 0;
	TDPRINTF("Creating TScheduler.\n");
}

TTask* TScheduler::CreateTask(TClass const& a_rTaskClass, TTask* a_pTask)
{
	TASSERT(a_rTaskClass.IsA(TGetClass(TTask)) == TTRUE);
	TTask *pTask = static_cast<TTask*>(a_rTaskClass.CreateObject());
	TASSERT(pTask != TNULL);
	m_oTaskTree.InsertAtRoot(pTask);
	if (a_pTask) {
		m_oTaskTree.Remove(pTask, TFALSE);
		m_oTaskTree.Insert(a_pTask, pTask);
	}
	return pTask;
}

void TScheduler::Update()
{
	if (Profiler_Control_ParentStart) {
		Profiler_Program.Start();
		Profiler_Control_ParentStart = TFALSE;
	}
	if (Profiler_Control_ParentStop) {
		Profiler_Program.Stop();
		TProfiler::PrintSummary();
		Profiler_Control_ParentStop = TFALSE;
	}
	TFLOAT deltaTime = m_pKernel->GetSystemTimer()->GetDelta();
	m_fTotalTime += deltaTime;
	m_iFrameCount++;

	// Control delta time
	if (deltaTime >= 0.0f) {
		if (deltaTime >= m_fDebugSlowTime) {
			m_fCurrentTimeDelta = m_fDebugSlowTime;
		}
		else {
			m_fCurrentTimeDelta = deltaTime;
		}
	}
	else {
		m_fCurrentTimeDelta = 0.0f;
	}

	DestroyDyingTasks(m_oTaskTree.ChildOfRoot());
	UpdateActiveTasks(m_oTaskTree.ChildOfRoot());
}

void TScheduler::DestroyDyingTasks(TTask* a_pTask)
{
	if (a_pTask != TNULL)
	{
		TTask* currentTask = a_pTask->Prev();

		while (currentTask != TNULL)
		{
			TTask* nextTask = (currentTask->Prev() != a_pTask) ? currentTask->Prev() : TNULL;

			if (!currentTask->IsDying())
			{
				if (currentTask->Child() != TNULL)
				{
					DestroyDyingTasks(currentTask->Child());
				}
			}
			else
			{
				DeleteTask(currentTask);
			}

			currentTask = nextTask;
		}
	}
	/*
	if (!a_pTask) return;
	for (TTask* pTask = a_pTask->Prev(); pTask != TNULL; pTask = (pTask->Prev() != a_pTask) ? a_pTask->Prev() : TNULL) {
		if (!pTask->IsDying()) {
			if (pTask->Child() != TNULL) {
				DestroyDyingTasks(pTask->Child());
			}
		}
		else {
			DeleteTask(pTask);
		}
	}*/
}

void TScheduler::DestroyTaskRecurse(TTask* a_pTask)
{
	for (TTask* pTask = a_pTask; pTask != TNULL; pTask = (pTask->Next() != a_pTask) ? a_pTask->Next() : TNULL) {
		pTask->m_Flags |= TTask::State_Dying;

		if (pTask->Child() != TNULL) {
			DestroyTaskRecurse(pTask->Child());
		}
	}
}

void TScheduler::UpdateActiveTasks(TTask* a_pTask)
{
	TTask* currentTask = a_pTask;

	while (currentTask != TNULL)
	{
		TTask* nextTask = (currentTask->Next() != a_pTask) ? currentTask->Next() : TNULL;

		TBOOL recurse = TTRUE;
		if (a_pTask->IsCreated() && a_pTask->IsActive())
		{
			recurse = currentTask->OnUpdate(m_fCurrentTimeDelta);
		}

		if (currentTask->Child() != TNULL && recurse)
		{
			UpdateActiveTasks(currentTask->Child());
		}

		currentTask = nextTask;
	}
	/*for (TTask* pTask = a_pTask; pTask != TNULL; pTask = (pTask->Next() != a_pTask) ? a_pTask->Next() : TNULL) {
		TBOOL recurse = TTRUE;
		if (pTask->IsCreated() && pTask->IsActive()) {
			recurse = pTask->OnUpdate(m_fCurrentTimeDelta);
		}

		if (pTask->Child() != TNULL && recurse) {
			UpdateActiveTasks(pTask->Child());
		}
	}*/
}

void TScheduler::DestroyAllTasks()
{
	TTask* pAttached = m_oTaskTree.ChildOfRoot();
	if (pAttached) {
		DestroyTask(*pAttached);
		DeleteTaskAtomic(pAttached);
	}
}

void TScheduler::DestroyTask(TTask& a_rTask)
{
	if (!a_rTask.IsDying()) {
		a_rTask.m_Flags |= TTask::State_Dying;
		DestroyTaskRecurse(&a_rTask);
	}
}

void TScheduler::DeleteTask(TTask* a_pTask)
{
	DeleteTaskRecurse(a_pTask->Child());
	DeleteTaskAtomic(a_pTask);
}

void TScheduler::DeleteTaskRecurse(TTask* a_pTask)
{
	if (!a_pTask) return;
	for (TTask* pTask = a_pTask->Prev(); pTask != TNULL; pTask = (pTask->Prev() != a_pTask) ? a_pTask->Prev() : TNULL) {
		DeleteTaskAtomic(pTask);
	}
}

void TScheduler::DeleteTaskAtomic(TTask* a_pTask)
{
	if (!a_pTask) return;
	TTask* taskParent = TNULL;

	if (a_pTask->IsChildOfDefaultRoot() == TFALSE) {
		taskParent = a_pTask->Parent();

		if (taskParent->IsDying() == TFALSE && taskParent->OnChildDying(a_pTask) == TFALSE) {
			// The parent is not dying and doesn't allow us to kill the task
			return;
		}
	}

	if (a_pTask->Child() != TNULL) {
		DeleteTaskRecurse(a_pTask->Child());
	}

	TClass* pClass = &a_pTask->GetClass();
	a_pTask->OnDestroy();
	m_oTaskTree.Remove(a_pTask, TFALSE);
	a_pTask->Delete();

	if (taskParent != TNULL) {
		taskParent->OnChildDied(pClass, a_pTask);
	}
}
