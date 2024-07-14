#pragma once
#include "TKernel/TTask.h"
#include "TKernel/TCString.h"

class ADummyTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ADummyTask);
public:
	ADummyTask() = default;
	virtual ~ADummyTask() = default;

	// Shouldn't a_szName be TPCCHAR? [7/8/2024 InfiniteC0re]
	void SetName(TPCHAR a_szName)
	{
		m_szName = a_szName;
	}

	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override
	{
		return TTask::OnUpdate(a_fDeltaTime);
	}

private:
	Toshi::TCString m_szName;
};