#include "main.h"

AApplication g_oTheApp;

TBOOL AApplication::OnCreate(TINT argc, TPCHAR* const argv)
{
	m_pInputTask = (ADummyTask*)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), TNULL);
	m_pInputTask->Create();
	m_pInputTask->Activate(TTRUE);
	TPCHAR str = (TPCHAR)"InputTask";
	m_pInputTask->SetName(str);

	return TApplication::OnCreate(argc, argv);
}

int main(int argc, char** argv)
{
	if (g_oTheApp.Create("Jurassic Park: Operation Genesis - (c) Blue Tongue Software", argc, argv)) {
		Toshi::TMemory::DebugPrintHALMemInfo(TNULL);
		g_oTheApp.Execute();
	}
	g_oTheApp.Destroy();
	return 0;
}