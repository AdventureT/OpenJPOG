#include "AGUISystem.h"
#include "main.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AGUISystem, TTask)

// $JPOG: FUNCTION 0067b380
AGUISystem::AGUISystem()
{
	m_pGUIInterface = TNULL;
}

// $JPOG: FUNCTION 0067bc30
TBOOL AGUISystem::OnCreate()
{
	auto pRenderer  = g_oTheApp.GetRootTask()->GetRenderInterface();
	m_pNullResource = (TNullResource *)pRenderer->CreateResource(&TGetClass(TNullResource), TNULL, TNULL);
	m_pSpriteShader = (TSpriteShader *)pRenderer->CreateResource(TFindClass(TSpriteShaderHAL, TNULL), "SHSPRITE", pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SHADERS));
	m_pGUIInterface->Create();
	m_pDisplayContext = new PGUITRDisplayContext();
	m_pDisplayContext->Create(g_oTheApp.GetRootTask()->GetRenderInterface(), m_pTextureFactory, m_pFontFactory);
	m_pScreen = new TGUIScreen();
	TCString guiTexturePath = TCString("data/gui/textures");
	//m_oPaintListener.Connect(*m_pScreen->GetPaintEmitter(), this, OnScreenPaint, -0x8000);
	m_pMatLibPic = new AGUIMatLibPicture();
	m_pMatLibPic->Create(guiTexturePath, m_pSpriteShader);
	return true;
}

// $JPOG: FUNCTION 0067c1f0
TBOOL AGUISystem::OnUpdate(TFLOAT a_fDeltaTime)
{
	TCString &rCurFileName = g_oTheApp.GetRootTask()->GetRootStateController()->GetCurrentGameState().GetHUDState().m_szBKGMatLib;
	if (rCurFileName != m_pMatLibPic->GetFileName()) {
		m_pMatLibPic->SetFile(rCurFileName);
		if (!rCurFileName.IsEmpty()) {
			m_pMatLibPic->Cache();
		}
	}
	return TTRUE;
}

void AGUISystem::UpdateHUDComponets()
{
}

// $JPOG: FUNCTION 0067e3f0
AGUISystem *TOSHI_API AGUISystem::GetGUISystem()
{
	return g_oTheApp.GetRootTask()->GetGUISystem();
}

// $JPOG: FUNCTION 0067de10
TBOOL AGUISystem::OnScreenPaint(AGUISystem *a_pGUISystem, TGUIScreen *a_pScreen, TGUIScreenPaintEvent *a_pEvent)
{
	static TBOOL paint = TTRUE;
	if (!paint) {
		return TTRUE;
	}
	if (!a_pEvent) {
		return TTRUE;
	}
	a_pGUISystem->m_pMatLibPic->Render();
	AMoviePlayer *movieplayer = g_oTheApp.GetRootTask()->GetMoviePlayer();
	if (movieplayer) {
		movieplayer->Render();
	}
	return TTRUE;
}
