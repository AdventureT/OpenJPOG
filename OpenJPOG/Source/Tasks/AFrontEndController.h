#pragma once
#include "TKernel/TTask.h"

class AFrontEndController : public Toshi::TTask
{
	DECLARE_DYNAMIC(AFrontEndController)

public:
	// $JPOG: FUNCTION 00484fd0
	virtual TBOOL OnCreate() override
	{
		return TTask::OnCreate();
	}
	// $JPOG: FUNCTION 00484fc0
	virtual void OnDestroy() override
	{
		TTask::OnDestroy();
	}
};
