#include "main.h"
#include "TRender/TResource.h"

AApplication g_oTheApp;

TBOOL AApplication::OnCreate(TINT argc, TPCHAR *const argv)
{
	m_pRenderTask = (ADummyTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pRenderTask->Create();
	m_pRenderTask->Activate(TTRUE);
	m_pRenderTask->SetName((TPCHAR) "RenderTask");

	m_pUpdate3Task = (ADummyTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pUpdate3Task->Create();
	m_pUpdate3Task->Activate(TTRUE);
	m_pUpdate3Task->SetName((TPCHAR) "Update3");

	m_pUpdate2Task = (ADummyTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pUpdate2Task->Create();
	m_pUpdate2Task->Activate(TTRUE);
	m_pUpdate2Task->SetName((TPCHAR) "Update2");

	m_pUpdate1Task = (ADummyTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pUpdate1Task->Create();
	m_pUpdate1Task->Activate(TTRUE);
	m_pUpdate1Task->SetName((TPCHAR) "Update1");

	m_pInputTask = (ADummyTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pInputTask->Create();
	m_pInputTask->Activate(TTRUE);
	m_pInputTask->SetName((TPCHAR) "InputTask");

	m_pRootTask = (ARootTask *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ARootTask), m_pUpdate2Task);
	if (m_pRootTask) {
		if (!m_pRootTask->Create()) {
			return TFALSE;
		}
		m_pRootTask->Activate(TTRUE);
	}

	return TApplication::OnCreate(argc, argv);
}

TBOOL AApplication::OnDestroy()
{
	m_pRootTask->DestroyTask();
	m_pInputTask->DestroyTask();
	m_pRenderTask->DestroyTask();
	return TTRUE;
}

int main(int argc, char **argv)
{
	if (g_oTheApp.Create("Jurassic Park: Operation Genesis - (c) Blue Tongue Software", argc, argv)) {
		Toshi::TMemory::DebugPrintHALMemInfo(TNULL);
		g_oTheApp.Execute();
	}
	g_oTheApp.Destroy();
	return 0;
}
