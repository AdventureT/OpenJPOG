#include "ARootTask.h"
#include "Movie/ABINKMoviePlayer.h"
#include "main.h"
#include "States/AFrontEndSplashState.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootTask, TTask);

// $JPOG: FUNCTION 0047a120
ARootTask::ARootTask()
{
	m_pOptions             = TNULL;
	m_pGUISystem           = TNULL;
	m_pInputTask           = TNULL;
	m_pRenderInterface     = TNULL;
	m_pRenderer            = TNULL;
	m_pGameStateController = TNULL;
	m_pVibrationTask       = TNULL;
	m_pMoviePlayer         = TNULL;
	m_pOptions             = new AOptions();
	AllocateRenderInterface();
	AllocateGUISystem();
	AllocateARenderer();
	AllocateGameStateController();
	m_pMoviePlayer = TNULL;
}

// $JPOG: FUNCTION 0047a580
TBOOL ARootTask::OnCreate()
{
	m_pMoviePlayer = new ABINKMoviePlayer();
	if (!CreateRenderInterface()) {
		return TFALSE;
	}
	m_pOptions->LoadOptions();
	DeserialiseOptions();
	CreateARenderer();
	CreateGameStateController();
	GetRootStateController()->TransferControl(new AFrontEndSplashState());
	return TTask::OnCreate();
}

// $JPOG: FUNCTION 0047d1e0
void ARootTask::OnDestroy()
{
	TTask::OnDestroy();
}

// $JPOG: FUNCTION 0047a720
void ARootTask::OnChildDied(TClass *a_pClass, TTask *a_pDeletedTask)
{
	TTask::OnChildDied(a_pClass, a_pDeletedTask);
}

// $JPOG: FUNCTION 0047a440
void ARootTask::OnActivate()
{
	if (GetRootStateController()) {
		GetRootStateController()->Activate(TTRUE);
	}
	if (GetARenderer()) {
		GetARenderer()->Activate(TTRUE);
	}
	TTask::OnActivate();
}

// $JPOG: FUNCTION 0047a4e0
void ARootTask::OnDeactivate()
{
	if (GetRootStateController()) {
		GetRootStateController()->Activate(TFALSE);
	}
	if (GetARenderer()) {
		GetARenderer()->Activate(TFALSE);
	}
	TTask::OnDeactivate();
}

// $JPOG: FUNCTION 0047b6b0
void ARootTask::LoadFrontEndController()
{
	m_pFrontEndController = (AFrontEndController *)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(AFrontEndController), this);
	m_pFrontEndController->Create();
	LoadMaterialLibrary(1);
	LoadMaterialLibrary(25);
	g_oTheApp.GetKernel()->GetSystemTimer()->Reset();
}

// $JPOG: FUNCTION 0047b700
void ARootTask::UnloadFrontEndController()
{
}

// $JPOG: FUNCTION 0047c680
void ARootTask::AllocateARenderer()
{
	m_pRenderer = ApplicationCreateTask(ARenderer, g_oTheApp.GetRenderRootTask());
}

// $JPOG: FUNCTION 0047c5e0
void ARootTask::AllocateRenderInterface()
{
	g_oTheApp.GetKernel()->LoadInterface("TRenderD3DInterface");
	m_pRenderInterface = (TRenderInterface *)TFindClass(TRenderD3DInterface, TNULL)->CreateObject();
	m_pRenderInterface->Create(g_oTheApp.GetKernel());
	m_pRenderInterface->DumpStats();
}

// $JPOG: FUNCTION 0047c750
void ARootTask::AllocateGameStateController()
{
	m_pGameStateController = ApplicationCreateTask(ARootStateController, this);
}

// $JPOG: FUNCTION 0047c710
void ARootTask::AllocateGUISystem()
{
	m_pGUISystem = ApplicationCreateTask(AGUISystem, g_oTheApp.GetUpdate3RootTask());
}

// $JPOG: FUNCTION 0047c6c0
void ARootTask::AllocateInputSystem()
{
	m_pInputTask     = ApplicationCreateTask(ADummyTask, g_oTheApp.GetInputRootTask());
	m_pVibrationTask = ApplicationCreateTask(AVibrationManager, g_oTheApp.GetInputRootTask());
}

// $JPOG: FUNCTION 0047cb80
void ARootTask::CreateARenderer()
{
	if (m_pRenderer && m_pRenderer->Create()) {
		return;
	}
	m_pRenderer = TNULL;
}

// $JPOG: FUNCTION 0047c7e0
TBOOL ARootTask::CreateRenderInterface()
{
	TRenderInterface::DisplayParams displayParams;
	displayParams.uiWidth             = 640;
	displayParams.uiHeight            = 480;
	displayParams.bWindowed           = TTRUE;
	displayParams.uiColourDepth       = 32;
	displayParams.eDepthStencilFormat = 0;
	CreateDisplayDevice(displayParams, TFALSE);
	m_pRenderInterface->CreateDisplay(displayParams);
	return TTRUE;
}

// $JPOG: FUNCTION 0047d1b0
void ARootTask::CreateGameStateController()
{
	GetRootStateController()->Create();
}

// $JPOG: FUNCTION 0047c070
void ARootTask::DeserialiseOptions()
{
	TRenderInterface *renderer = g_oTheApp.GetRootTask()->m_pRenderInterface;
	renderer->GetCurrentDisplayParams();
	AOptions     *options = g_oTheApp.GetRootTask()->GetOptions();
	AOptionsLogic logic;
	TINT          screenWidth;
	TINT          screenHeight;
	TINT          screenDepth;
	if (options->GetOption("ScreenWidth", screenWidth) &&
	    options->GetOption("ScreenHeight", screenHeight) &&
	    options->GetOption("ScreenDepth", screenDepth)) {
		AOptionsLogic::AScreenRes screenRes;
		logic.GetOption(AOptionsLogic::OPTION_SCREENRES, screenRes);
	}
}

// $JPOG: FUNCTION 0047cea0
const TRenderAdapter::Mode::Device *ARootTask::CreateDisplayDevice(TRenderInterface::DisplayParams &a_rDisplayParams, bool a_bReverseOrder)
{
	TRenderInterface                   *pRenderer = TRenderInterface::GetRenderer();
	const TRenderAdapter::Mode::Device *pDevice   = TNULL;

	if (a_bReverseOrder)
	{
		a_rDisplayParams.eDepthStencilFormat = 4;
		pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

		if (!pDevice)
		{
			a_rDisplayParams.eDepthStencilFormat = 2;
			pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

			if (!pDevice)
			{
				a_rDisplayParams.eDepthStencilFormat = 3;
				pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

				if (!pDevice)
				{
					a_rDisplayParams.eDepthStencilFormat = 0;
					pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

					if (!pDevice)
					{
						a_rDisplayParams.eDepthStencilFormat = 1;
						pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);
					}
				}
			}
		}
	}
	else
	{
		pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);
		a_rDisplayParams.eDepthStencilFormat = 0;

		if (!pDevice)
		{
			a_rDisplayParams.eDepthStencilFormat = 1;
			pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

			if (!pRenderer->FindDevice(&a_rDisplayParams))
			{
				a_rDisplayParams.eDepthStencilFormat = 2;
				pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

				if (!pRenderer->FindDevice(&a_rDisplayParams))
				{
					a_rDisplayParams.eDepthStencilFormat = 4;
					pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);

					if (!pRenderer->FindDevice(&a_rDisplayParams))
					{
						a_rDisplayParams.eDepthStencilFormat = 3;
						pDevice                              = pRenderer->FindDevice(&a_rDisplayParams);
					}
				}
			}
		}
	}

	return pDevice;
}

// $JPOG: FUNCTION 0047b780
void ARootTask::LoadMaterialLibrary(TINT a_iIndex)
{
}
