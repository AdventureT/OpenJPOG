#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"
#include "AVibrationManager.h"

class ARootTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);
public:
	ARootTask() = default;
	virtual ~ARootTask() = default;

	void SetName(TPCHAR a_szName)
	{
		m_szName = a_szName;
	}

private:
	void AllocateInputSystem();

private:
	Toshi::TCString m_szName;
	TTask* m_pInputTask;      // 0x38
	AVibrationManager* m_pVibrationTask; // 0xE8
};