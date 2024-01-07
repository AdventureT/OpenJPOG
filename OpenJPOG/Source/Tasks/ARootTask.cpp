#include "ARootTask.h"
#include "Movie/ABINKMoviePlayer.h"
#include "main.h"
#include "States/AFrontEndSplashState.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARootTask, TTask);

ARootTask::ARootTask()
{
	m_pGUISystem = TNULL;
	m_pInputTask = TNULL;
	m_pRenderInterface = TNULL;
	m_pRenderer = TNULL;
	m_pGameStateController = TNULL;
	m_pVibrationTask = TNULL;
	m_pMoviePlayer = TNULL;
	AllocateRenderInterface();
	AllocateGameStateController();
	m_pMoviePlayer = TNULL;
}

TBOOL ARootTask::OnCreate()
{
	m_pMoviePlayer = new ABINKMoviePlayer();
	if (!CreateRenderInterface()) {
		return TFALSE;
	}
	CreateARenderer();
	CreateGameStateController();
	GetRootStateController()->TransferControl(new AFrontEndSplashState());
	return TTask::OnCreate();
}

void ARootTask::OnDestroy()
{
}

void ARootTask::OnChildDied(TClass* a_pClass, TTask* a_pDeletedTask)
{
}

void ARootTask::OnActivate()
{
	if (GetRootStateController()) {
		GetRootStateController()->Activate(TTRUE);
	}
	if (GetARenderer()) {
		GetARenderer()->Activate(TTRUE);
	}
}

void ARootTask::OnDeactivate()
{
}

void ARootTask::LoadFrontEndController()
{
}

void ARootTask::UnloadFrontEndController()
{
}

void ARootTask::AllocateARenderer()
{
	m_pRenderer = (ARenderer*)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ARenderer), g_oTheApp.GetRenderRootTask());
}

void ARootTask::AllocateRenderInterface()
{
	g_oTheApp.GetKernel()->LoadInterface("TRenderD3DInterface");
	m_pRenderInterface = (TRenderInterface*)TFindClass(TRenderD3DInterface, TNULL)->CreateObject();
	m_pRenderInterface->Create(g_oTheApp.GetKernel());
	m_pRenderInterface->DumpStats();
}

void ARootTask::AllocateGameStateController()
{
	m_pGameStateController = (ARootStateController*)g_oTheApp.GetKernel()->GetScheduler()->CreateTask(TGetClass(ARootStateController), this);
}

void ARootTask::AllocateInputSystem()
{
	TScheduler* pScheduler = g_oTheApp.GetKernel()->GetScheduler();
	ADummyTask* pInputTask = g_oTheApp.GetInputRootTask();
	m_pInputTask = pScheduler->CreateTask(TGetClass(ADummyTask), pInputTask);
	m_pVibrationTask = (AVibrationManager*)pScheduler->CreateTask(TGetClass(AVibrationManager), pInputTask);
}

void ARootTask::CreateARenderer()
{
	if (m_pRenderer && m_pRenderer->Create()) {
		return;
	}
	m_pRenderer = TNULL;
}

TBOOL ARootTask::CreateRenderInterface()
{
	TRenderInterface::DisplayParams displayParams;
	displayParams.uiWidth = 640;
	displayParams.uiHeight = 480;
	displayParams.bWindowed = TTRUE;
	displayParams.uiColourDepth = 32;
	displayParams.eDepthStencilFormat = 0;
	CreateDisplayDevice(displayParams, TFALSE);
	m_pRenderInterface->CreateDisplay(displayParams);
	return TTRUE;
}

void ARootTask::CreateGameStateController()
{
	GetRootStateController()->Create();
}

const TRenderAdapter::Mode::Device* ARootTask::CreateDisplayDevice(TRenderInterface::DisplayParams& a_rDisplayParams, bool a_bReverseOrder)
{
	TRenderInterface* pRenderer = TRenderInterface::GetRenderer();
	const TRenderAdapter::Mode::Device* pDevice = TNULL;

	if (a_bReverseOrder)
	{
		a_rDisplayParams.eDepthStencilFormat = 4;
		pDevice = pRenderer->FindDevice(&a_rDisplayParams);

		if (!pDevice)
		{
			a_rDisplayParams.eDepthStencilFormat = 2;
			pDevice = pRenderer->FindDevice(&a_rDisplayParams);

			if (!pDevice)
			{
				a_rDisplayParams.eDepthStencilFormat = 3;
				pDevice = pRenderer->FindDevice(&a_rDisplayParams);

				if (!pDevice)
				{
					a_rDisplayParams.eDepthStencilFormat = 0;
					pDevice = pRenderer->FindDevice(&a_rDisplayParams);

					if (!pDevice)
					{
						a_rDisplayParams.eDepthStencilFormat = 1;
						pDevice = pRenderer->FindDevice(&a_rDisplayParams);
					}
				}
			}
		}
	}
	else
	{
		pDevice = pRenderer->FindDevice(&a_rDisplayParams);
		a_rDisplayParams.eDepthStencilFormat = 0;

		if (!pDevice)
		{
			a_rDisplayParams.eDepthStencilFormat = 1;
			pDevice = pRenderer->FindDevice(&a_rDisplayParams);

			if (!pRenderer->FindDevice(&a_rDisplayParams))
			{
				a_rDisplayParams.eDepthStencilFormat = 2;
				pDevice = pRenderer->FindDevice(&a_rDisplayParams);

				if (!pRenderer->FindDevice(&a_rDisplayParams))
				{
					a_rDisplayParams.eDepthStencilFormat = 4;
					pDevice = pRenderer->FindDevice(&a_rDisplayParams);

					if (!pRenderer->FindDevice(&a_rDisplayParams))
					{
						a_rDisplayParams.eDepthStencilFormat = 3;
						pDevice = pRenderer->FindDevice(&a_rDisplayParams);
					}
				}
			}
		}
	}

	return pDevice;

}
