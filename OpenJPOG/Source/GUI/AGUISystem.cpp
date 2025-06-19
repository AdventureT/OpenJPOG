#include "AGUISystem.h"
#include "main.h"
#include "TSpriteShader/Include/D3D/TSpriteShaderD3D.h"
#include "TRender/TScene.h"

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
	m_pDisplayContext = TNULL;
	m_pTextureFactory = TNULL;
	m_pFontFactory    = TNULL;
	m_pGUIInterface   = static_cast<TGUIInterface *>(TFindClass(TGUIInterface, TNULL)->CreateObject());
	m_pGUIInterface->SetKernelInterface(g_oTheApp.GetKernel());
	m_pTextureFactory = new AGUITextureFactory();
}

// $JPOG: FUNCTION 0067bc30
TBOOL AGUISystem::OnCreate()
{
	auto pRenderer  = g_oTheApp.GetRootTask()->GetRenderInterface();
	m_pNullResource = (TNullResource *)pRenderer->CreateResource(&TGetClass(TNullResource), TNULL, TNULL);
	TClass *pClass  = &TGetClass(TSpriteShaderHAL);
	m_pSpriteShader = (TSpriteShader *)pRenderer->CreateResource(TFindClass(TSpriteShaderHAL, TNULL), "SHSPRITE", pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_SHADERS));
	m_pSpriteShader->Create();
	m_pGUIInterface->Create();
	m_pDisplayContext = new PGUITRDisplayContext();
	m_pDisplayContext->Create(g_oTheApp.GetRootTask()->GetRenderInterface(), m_pTextureFactory, m_pFontFactory);
	auto pDisplayParams = pRenderer->GetCurrentDisplayParams();
	m_pScreen = new TGUIScreen();
	m_pScreen->SetSize(TMIN(800, pDisplayParams->uiWidth), TMIN(600, pDisplayParams->uiHeight));
	m_pScreen->SetDisplayContext(m_pDisplayContext);
	m_pScreen->SetState(STATE_VISIBLE, STATE_VISIBLE);
	m_oScreenPaintListener.Connect(m_pScreen->GetPaintEmitter(), this, OnScreenPaint, -0x8000);
	for (TINT i = 0; i < 2; i++) {
		TCString sceneName = TCString().Format("Scene%d", i);
		m_pScenes[i] = static_cast<TScene *>(pRenderer->CreateResource(&TGetClass(TScene), sceneName, TNULL));
		m_pScenes[i]->Create();
		m_pScenes[i]->CreateViewport("GUIViewport", TNULL, TRUE);
	}
	// m_pScreen->SetAudioContext
	// m_pScreen->SetInputContext
	TCString guiTexturePath = TCString("data/gui/textures");
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
