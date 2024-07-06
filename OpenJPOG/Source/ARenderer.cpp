#include "ARenderer.h"
#include "main.h"


TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARenderer, TTask)

const TFLOAT ARenderer::ms_fMainZMax = 1.0f;
const TFLOAT ARenderer::ms_fMainZMin = 0.0f;
const TFLOAT ARenderer::ms_fSkyZMax  = 1.0f;
const TFLOAT ARenderer::ms_fSkyZMin  = 0.0f;

const TMatrix44 ARenderer::ms_mLightCol = TMatrix44();
const TMatrix44 ARenderer::ms_mLightDir = TMatrix44();

ARenderer::ARenderer()
{
	m_pViewport = TNULL;
	m_fFarClip = 160.0f;
	m_pcScreenCaptureBuffer = TNULL;
}

TBOOL ARenderer::OnCreate()
{
	TRenderInterface* pRenderer = TRenderInterface::GetRenderer();
	//pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSYS);
	//pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SCENE);
	return TTask::OnCreate();
}

TBOOL ARenderer::OnUpdate(TFLOAT a_fDeltaTime)
{
	UpdateMovie(a_fDeltaTime);
	g_oTheApp.GetRootTask()->GetRenderInterface()->Update(a_fDeltaTime);
	return TTask::OnUpdate(a_fDeltaTime);
}

void ARenderer::UpdateMovie(TFLOAT a_fDeltaTime)
{
	ARootStateController* pGameStateController = g_oTheApp.GetRootTask()->GetRootStateController();
	AMoviePlayer* pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();

	if (pMoviePlayer && pMoviePlayer->IsMoviePlaying()) {
		pMoviePlayer->Update(a_fDeltaTime);
	}
}
