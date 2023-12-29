#include "ARootTask.h"
#include "main.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootTask, TTask);

ARootTask::ARootTask()
{
	m_pMoviePlayer = TNULL;
}

TBOOL ARootTask::OnCreate()
{
	m_pMoviePlayer = new ABINKMoviePlayer();
	return TTask::OnCreate();
}

void ARootTask::AllocateInputSystem()
{
	TScheduler* pScheduler = g_oTheApp.GetKernel()->GetScheduler();
	ADummyTask* pInputTask = g_oTheApp.GetInputRootTask();
	m_pInputTask = pScheduler->CreateTask(TGetClass(ADummyTask), pInputTask);
	m_pVibrationTask = (AVibrationManager*)pScheduler->CreateTask(TGetClass(AVibrationManager), pInputTask);
}
