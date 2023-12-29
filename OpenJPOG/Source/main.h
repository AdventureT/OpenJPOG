#pragma once
#include "TApplication/TApplication.h"
#include "TKernel/TMemory.h"
#include "ADummyTask.h"
#include "ARootTask.h"

class AApplication : public Toshi::TApplication
{
public:

	AApplication()
	{

	}

	virtual TBOOL OnCreate(TINT argc, TPCHAR* const argv) override;
	virtual TBOOL OnDestroy() override;
public:
	ARootTask* GetRootTask() const { return m_pRootTask; }
	ADummyTask* GetInputRootTask() const { return m_pInputTask; }
	ADummyTask* GetUpdate1RootTask() const { return m_pUpdate1Task; }
	ADummyTask* GetUpdate2RootTask() const { return m_pUpdate2Task; }
	ADummyTask* GetUpdate3RootTask() const { return m_pUpdate3Task; }
	ADummyTask* GetRenderRootTask() const { return m_pRenderTask; }

private:
	                            // 0x0 -> 0x1C TApplication 
	ARootTask* m_pRootTask;     // 0x1C
	ADummyTask* m_pInputTask;   // 0x20
	ADummyTask* m_pUpdate1Task; // 0x24
	ADummyTask* m_pUpdate2Task; // 0x28
	ADummyTask* m_pUpdate3Task; // 0x2C
	ADummyTask* m_pRenderTask;  // 0x24
};

extern AApplication g_oTheApp;