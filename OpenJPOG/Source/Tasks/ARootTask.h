#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"
#include "AVibrationManager.h"
#include "Movie/AMoviePlayer.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TManagedPointer.h"
#include "GUI/AGUISystem.h"
#include "ARootStateController.h"
#include "ARenderer.h"
#include "Tasks/AFrontEndController.h"
#include "AOptions.h"

class ARootTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);

public:
	ARootTask();
	virtual ~ARootTask() = default;

	virtual TBOOL OnCreate() override;
	// $JPOG: FUNCTION 0047d3a0
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override { return TTRUE; }
	virtual void  OnDestroy() override;
	virtual void  OnChildDied(Toshi::TClass *a_pClass, Toshi::TTask *a_pDeletedTask) override;
	virtual void  OnActivate() override;
	virtual void  OnDeactivate() override;

	void LoadFrontEndController();
	void UnloadFrontEndController();

	static void DeserialiseOptions();

	void SetName(TPCHAR a_szName)
	{
		m_szName = a_szName;
	}

	// $JPOG: FUNCTION 004661b0
	AOptions *GetOptions()
	{
		return m_pOptions;
	}
	// $JPOG: FUNCTION 00466150
	//Toshi::TManagedPtr<Toshi::TRenderInterface>!!!
	Toshi::TManagedPtr<Toshi::TRenderInterface> GetRenderInterface()
	{
		return m_pRenderInterface;
	}
	// $JPOG: FUNCTION 0047d370
	AGUISystem *GetGUISystem()
	{
		return m_pGUISystem;
	}
	// $JPOG: FUNCTION 004660c0
	Toshi::AMoviePlayer *GetMoviePlayer()
	{
		return m_pMoviePlayer;
	}
	// $JPOG: FUNCTION 0047d340
	ARootStateController *GetRootStateController() const
	{
		return m_pGameStateController;
	}
	// $JPOG: FUNCTION 00466140
	Toshi::ARenderer *GetARenderer()
	{
		return m_pRenderer;
	}

private:
	void AllocateARenderer();
	void AllocateRenderInterface();
	void AllocateGameStateController();
	void AllocateGUISystem();
	void AllocateInputSystem();

	void  CreateARenderer();
	TBOOL CreateRenderInterface();
	void  CreateGameStateController();
	void  CreateGUISystem();

	const Toshi::TRenderAdapter::Mode::Device *CreateDisplayDevice(Toshi::TRenderInterface::DisplayParams &a_rDisplayParams, bool a_bReverseOrder);

	void LoadMaterialLibrary(TINT a_iIndex);

private:
	Toshi::TCString                             m_szName;
	AOptions                                   *m_pOptions;             // 0x24
	AFrontEndController                        *m_pFrontEndController;  // 0x28
	AGUISystem                                 *m_pGUISystem;           // 0x34
	Toshi::TTask                               *m_pInputTask;           // 0x38
	Toshi::TManagedPtr<Toshi::TRenderInterface> m_pRenderInterface;     // 0xD0
	Toshi::ARenderer                           *m_pRenderer;            // 0xD4
	ARootStateController                       *m_pGameStateController; // 0xD8
	AVibrationManager                          *m_pVibrationTask;       // 0xE8
	Toshi::AMoviePlayer                        *m_pMoviePlayer;         // 0xF0
};
