#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"
#include "AVibrationManager.h"
#include "ABINKMoviePlayer.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TManagedPointer.h"

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

	Toshi::TManagedPtr<Toshi::TRenderInterface> GetRenderInterface() { return m_pRenderInterface; }

private:
	void AllocateInputSystem();

private:
	Toshi::TCString m_szName;
	Toshi::TTask* m_pInputTask;                 // 0x38
	Toshi::TRenderInterface* m_pRenderInterface;// 0xD0
	AVibrationManager* m_pVibrationTask;        // 0xE8
	Toshi::ABINKMoviePlayer* m_pMoviePlayer;    // 0xF0
};