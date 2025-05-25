#pragma once
#include "TApplication/TApplication.h"
#include "TKernel/TMemory.h"
#include "Tasks/ADummyTask.h"
#include "Tasks/ARootTask.h"

class AApplication : public Toshi::TApplication
{
public:
	// $JPOG: FUNCTION 00466020
	AApplication()
	{
	}

	virtual TBOOL OnCreate(TINT argc, TPCHAR *const argv) override;
	virtual TBOOL OnDestroy() override;

public:
	// $JPOG: FUNCTION 00484db0
	ARootTask  *GetRootTask() const { return m_pRootTask; }
	// $JPOG: FUNCTION 00484da0
	ADummyTask *GetInputRootTask() const { return m_pInputTask; }
	// $JPOG: FUNCTION 00484d90
	ADummyTask *GetUpdate1RootTask() const { return m_pUpdate1Task; }
	// $JPOG: FUNCTION 00484d80
	ADummyTask *GetUpdate2RootTask() const { return m_pUpdate2Task; }
	// $JPOG: FUNCTION 00484d70
	ADummyTask *GetUpdate3RootTask() const { return m_pUpdate3Task; }
	// $JPOG: FUNCTION 00484d60
	ADummyTask *GetRenderRootTask() const { return m_pRenderTask; }

private:
	// 0x0 -> 0x1C TApplication
	ARootTask  *m_pRootTask;    // 0x1C
	ADummyTask *m_pInputTask;   // 0x20
	ADummyTask *m_pUpdate1Task; // 0x24
	ADummyTask *m_pUpdate2Task; // 0x28
	ADummyTask *m_pUpdate3Task; // 0x2C
	ADummyTask *m_pRenderTask;  // 0x24
};

extern AApplication g_oTheApp;
