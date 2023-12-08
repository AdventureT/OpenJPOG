#include "TScheduler.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TScheduler, TObject);

TScheduler::TScheduler()
{
	m_pKernel = TNULL;
	m_fCurrentTimeDelta = 0.0f;
	m_fTotalTime = 0.0f;
	m_fDebugSlowTime = 1.0f;
	m_iFrameCount = 0;
	TDPRINTF("Creating TScheduler.\n");
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

	DestroyDyingTasks(m_oTaskTree.AttachedToRoot());
	UpdateActiveTasks(m_oTaskTree.AttachedToRoot());
}

void TScheduler::DestroyDyingTasks(TTask* a_pTask)
{
	if (!a_pTask) return;
	for (TTask* pTask = a_pTask->Prev(); pTask != TNULL; pTask = (pTask->Prev() != a_pTask) ? a_pTask->Prev() : TNULL) {
		if (!pTask->IsDying()) {
			if (pTask->Attached() != TNULL) {
				DestroyDyingTasks(pTask->Attached());
			}
		}
		else {
			DeleteTask(pTask);
		}
	}
}

void TScheduler::UpdateActiveTasks(TTask* a_pTask)
{
}

void TScheduler::DeleteTask(TTask* a_pTask)
{
	DeleteTaskRecurse(a_pTask->Attached());
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

	if (a_pTask->Attached() != TNULL) {
		DeleteTaskRecurse(a_pTask->Attached());
	}

	TClass* pClass = &a_pTask->GetClass();
	a_pTask->OnDestroy();
	m_oTaskTree.Remove(a_pTask, TFALSE);
	a_pTask->Delete();

	if (taskParent != TNULL) {
		taskParent->OnChildDied(pClass, a_pTask);
	}
}
