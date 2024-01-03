#pragma once

#include "TKernel/TTask.h"
#include "States/ARootState.h"

class ARootStateController : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);

public:
	ARootStateController();

	void TransferController(ARootState* a_pState);

public:
	ARootState* GetBaseAppState() { return m_pBaseAppState; }

private:
	ARootState* m_pBaseAppState; // 0x24
};

static inline ARootStateController* s_pCurrentStateController = TNULL;
