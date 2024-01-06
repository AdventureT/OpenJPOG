#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"
#include "AVibrationManager.h"
#include "Movie/AMoviePlayer.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TManagedPointer.h"
#include "GUI/AGUISystem.h"
#include "ARootStateController.h"


class ARootTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);
public:
	ARootTask();
	virtual ~ARootTask() = default;

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override { return TTRUE; }

	void LoadFrontEndController();
	void UnloadFrontEndController();

	void SetName(TPCHAR a_szName)
	{
		m_szName = a_szName;
	}

	Toshi::TManagedPtr<Toshi::TRenderInterface> GetRenderInterface() { return m_pRenderInterface; }
	AGUISystem* GetGUISystem() { return m_pGUISystem; }
	Toshi::AMoviePlayer* GetMoviePlayer() { return m_pMoviePlayer; }

private:
	void AllocateRenderInterface();
	void AllocateInputSystem();

	TBOOL CreateRenderInterface();
	const Toshi::TRenderAdapter::Mode::Device* CreateDisplayDevice(Toshi::TRenderInterface::DisplayParams& a_rDisplayParams, bool a_bReverseOrder);

private:
	Toshi::TCString m_szName;
	AGUISystem* m_pGUISystem;                     // 0x34
	Toshi::TTask* m_pInputTask;                   // 0x38
	Toshi::TRenderInterface* m_pRenderInterface;  // 0xD0
	ARootStateController* m_pGameStateController; // 0xD8
	AVibrationManager* m_pVibrationTask;          // 0xE8
	Toshi::AMoviePlayer* m_pMoviePlayer;          // 0xF0
};