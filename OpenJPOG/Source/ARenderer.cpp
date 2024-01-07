#include "ARenderer.h"
#include "main.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(ARenderer, TTask)

TBOOL ARenderer::OnCreate()
{
	TRenderInterface* pRenderer = TRenderInterface::GetRenderer();
	pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSYS);
	pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SCENE);
	return TBOOL();
}

TBOOL ARenderer::OnUpdate(TFLOAT a_fDeltaTime)
{
	UpdateMovie(a_fDeltaTime);
	g_oTheApp.GetRootTask()->GetRenderInterface()->Update(a_fDeltaTime);
	return TTRUE;
}

void ARenderer::UpdateMovie(TFLOAT a_fDeltaTime)
{
	ARootStateController* pGameStateController = g_oTheApp.GetRootTask()->GetRootStateController();
	AMoviePlayer* pMoviePlayer = g_oTheApp.GetRootTask()->GetMoviePlayer();

	if (pMoviePlayer && pMoviePlayer->IsMoviePlaying()) {
		pMoviePlayer->Update(a_fDeltaTime);
	}
}
