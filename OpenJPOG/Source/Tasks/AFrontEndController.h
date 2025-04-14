#pragma once
#include "TKernel/TTask.h"

class AFrontEndController : public Toshi::TTask
{
	DECLARE_DYNAMIC(AFrontEndController)

public:
	virtual TBOOL OnCreate() override
	{
		return TTask::OnCreate();
	}
	virtual void OnDestroy() override
	{
		TTask::OnDestroy();
	}
};
