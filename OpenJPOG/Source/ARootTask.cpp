#include "ARootTask.h"

class AApplication;
extern AApplication g_oTheApp;

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootTask, TTask);

void ARootTask::AllocateInputSystem()
{
	TScheduler* pScheduler = g_oTheApp.GetKernel()->GetScheduler();
	ADummyTask* pInputTask = g_oTheApp.GetInputRootTask();
	m_pInputTask = pScheduler->CreateTask(TGetClass(ADummyTask), pInputTask);
	m_pVibrationTask = (AVibrationManager*)pScheduler->CreateTask(TGetClass(AVibrationManager), pInputTask);

}
