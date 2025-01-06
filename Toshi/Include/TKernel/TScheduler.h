#pragma once

#include "TObject.h"
#include "TNodeTree.h"
#include "TTask.h"
#include "TProfiler.h"

TOSHI_NAMESPACE_BEGIN

class TKernelInterface;

class TKERNELINTERFACE_EXPORTS TScheduler : public TObject
{
	DECLARE_DYNAMIC(TScheduler);
public:

	TScheduler(TKernelInterface* a_pKernel);

	virtual ~TScheduler()
	{
		TDPRINTF("Destroying TScheduler.\n");
	}

	TTask* CreateTask(TClass const& a_rTaskClass, TTask* a_pTask);
	void Update();
	void DestroyDyingTasks(TTask *a_pTask);
	void DestroyAllTasks();
	void DestroyTask(TTask &a_rTask);

	void SetDebugSlowTime(TBOOL a_bEnable) { m_fDebugSlowTime = a_bEnable ? 0.01f : 1.0f; }

	// $TKernelInterface: FUNCTION 1002d690
	TKernelInterface* GetKernelInterface()
	{
		return m_pKernel;
	}

private:
	void DestroyTaskRecurse(TTask *a_pTask);
	void UpdateActiveTasks(TTask *a_pTask);
	void DeleteTask(TTask *a_pTask);
	void DeleteTaskRecurse(TTask *a_pTask);
	void DeleteTaskAtomic(TTask *a_pTask);
private:
	TTask *m_pCurrentTask;        // 0x4
	TKernelInterface *m_pKernel;  // 0x8
	TNodeTree<TTask> m_oTaskTree; // 0xC
	TFLOAT m_fCurrentTimeDelta;   // 0x24
	TFLOAT m_fTotalTime;          // 0x28
	TFLOAT m_fDebugSlowTime;      // 0x2C
	TFLOAT m_iFrameCount;         // 0x30
};

TOSHI_NAMESPACE_END