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
	//TKernelInterface *kernel = GetScheduler()->GetKernelInterface();
	//if (!kernel) {
	//	return false;
	//}
	MoviePlayerState state = RenderMovie(a_fDeltaTime);
	if (state != MOVIEPLAYERSTATE_RUNNING) {
		// Render things
	}
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

ARenderer::MoviePlayerState ARenderer::RenderMovie(TFLOAT a_fDeltaTime)
{
	ARootStateController * pGameStateController = g_oTheApp.GetRootTask()->GetRootStateController();
	AMoviePlayer *pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();
	if (!pMoviePlayer || !pMoviePlayer->IsMoviePlaying()) {
		return MOVIEPLAYERSTATE_STOPPED;
	}
	pMoviePlayer->Render_BackBufferBlit();
	return MOVIEPLAYERSTATE_RUNNING;
}

void ARenderer::CheckScreenCapture(TRenderInterface* a_pRenderer)
{
	switch (m_eCaptureState)
	{
	case Toshi::ARenderer::CAPTURESTATE_CREATE:
		m_pCapture = a_pRenderer->CreateCapture();
		m_pCapture->Create(TRenderCapture::FORMAT_RGBA32, m_iCaptureWidth, m_iCaptureHeight);
		m_pCapture->Request();
		m_eCaptureState = CAPTURESTATE_POLL;
		break;
	case Toshi::ARenderer::CAPTURESTATE_POLL:
		if (m_pCapture->Poll()) {
			m_eCaptureState = CAPTURESTATE_FINISHED;
			if (m_pcScreenCaptureBuffer) {
				delete m_pcScreenCaptureBuffer;
			}
			m_pcScreenCaptureBuffer = new TCHAR[m_iCaptureWidth * m_iCaptureHeight * 4];
			TSystem::MemCopy(m_pcScreenCaptureBuffer, m_pCapture->ObtainBuffer(), m_iCaptureWidth * m_iCaptureHeight * 4);
			m_pCapture->Destroy();
			a_pRenderer->DestroyCapture(m_pCapture);
			m_pCapture = TNULL;
		}
		break;
	default:
		break;
	}
}
