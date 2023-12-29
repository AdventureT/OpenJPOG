#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"
#include "AVibrationManager.h"
#include "ABINKMoviePlayer.h"

class ARootTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);
public:
	ARootTask();
	virtual ~ARootTask() = default;

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override { return TTRUE; }

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
	Toshi::ABINKMoviePlayer* m_pMoviePlayer;    // 0xF0
};