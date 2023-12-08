#pragma once

#include "TObject.h"
#include "TKernelInterface.h"
#include "TNodeTree.h"
#include "TTask.h"
#include "TProfiler.h"

TOSHI_NAMESPACE_BEGIN

TBOOL Profiler_Control_ParentStart = TFALSE;
TBOOL Profiler_Control_ParentStop  = TFALSE;
TProfiler Profiler_Program;

class TOSHI_EXPORT TScheduler : public TObject
{
	DECLARE_DYNAMIC(TKernelInterface);
public:

	TScheduler();

	void Update();
	void DestroyDyingTasks(TTask *a_pTask);
private:
	void UpdateActiveTasks(TTask *a_pTask);
	void DeleteTask(TTask *a_pTask);
	void DeleteTaskRecurse(TTask *a_pTask);
	void DeleteTaskAtomic(TTask *a_pTask);
private:
	TKernelInterface *m_pKernel;  // 0x8
	TNodeTree<TTask> m_oTaskTree; // 0xC
	TFLOAT m_fCurrentTimeDelta;   // 0x24
	TFLOAT m_fTotalTime;          // 0x28
	TFLOAT m_fDebugSlowTime;      // 0x2C
	TFLOAT m_iFrameCount;         // 0x30
};

TOSHI_NAMESPACE_END