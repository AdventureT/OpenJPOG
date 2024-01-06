#include "ARootTask.h"
#include "Movie/ABINKMoviePlayer.h"
#include "main.h"
#include "States/AFrontEndSplashState.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootTask, TTask);

ARootTask::ARootTask()
{
	AllocateRenderInterface();
	m_pMoviePlayer = TNULL;
}

TBOOL ARootTask::OnCreate()
{
	m_pMoviePlayer = new ABINKMoviePlayer();
	return TTask::OnCreate();
}

void ARootTask::LoadFrontEndController()
{
}

void ARootTask::UnloadFrontEndController()
{
}

void ARootTask::AllocateRenderInterface()
{
	g_oTheApp.GetKernel()->LoadInterface("TRenderD3DInterface");
	m_pRenderInterface = (TRenderInterface*)TFindClass(TRenderD3DInterface, TNULL)->CreateObject();
	m_pRenderInterface->Create(g_oTheApp.GetKernel());
	m_pRenderInterface->DumpStats();
}

void ARootTask::AllocateInputSystem()
{
	TScheduler* pScheduler = g_oTheApp.GetKernel()->GetScheduler();
	ADummyTask* pInputTask = g_oTheApp.GetInputRootTask();
	m_pInputTask = pScheduler->CreateTask(TGetClass(ADummyTask), pInputTask);
	m_pVibrationTask = (AVibrationManager*)pScheduler->CreateTask(TGetClass(AVibrationManager), pInputTask);
}
