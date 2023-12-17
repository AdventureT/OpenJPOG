#include "TApplication/TApplication.h"
#include "TKernel/TMemory.h"
#include "ADummyTask.h"

class AApplication : public Toshi::TApplication
{
	virtual TBOOL OnCreate(TINT argc, TPCHAR* const argv) override
	{

		m_pInputTask = (ADummyTask*)GetKernel()->GetScheduler()->CreateTask(TGetClass(ADummyTask), m_pInputTask);
		m_pInputTask->Create();
		m_pInputTask->Activate(TTRUE);
		m_pInputTask->SetName((TPCHAR)"InputTask");

		return TApplication::OnCreate(argc, argv);
	}
public:
	ADummyTask* GetInputRootTask() const { return m_pInputTask; }

private:
	// TApplication 0x0 -> 0x1C
	ADummyTask* m_pInputTask; // 0x1C
};

static AApplication g_oTheApp;

int main(int argc, char** argv)
{
	if (g_oTheApp.Create("Jurassic Park: Operation Genesis - (c) Blue Tongue Software", argc, argv)) {
		Toshi::TMemory::DebugPrintHALMemInfo(TNULL);
		g_oTheApp.Execute();
	}
	g_oTheApp.Destroy();
	return 0;
}