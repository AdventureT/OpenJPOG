#pragma once
#include "TApplication/TApplication.h"
#include "TKernel/TMemory.h"
#include "ADummyTask.h"

class AApplication : public Toshi::TApplication
{
public:

	AApplication()
	{

	}

	virtual TBOOL OnCreate(TINT argc, TPCHAR* const argv) override;
public:
	ADummyTask* GetInputRootTask() const { return m_pInputTask; }

private:
	// TApplication 0x0 -> 0x1C
	ADummyTask* m_pInputTask; // 0x1C
};

extern AApplication g_oTheApp;