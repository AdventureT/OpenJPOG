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
	m_pGUIInterface->Create();
	m_pDisplayContext = new PGUITRDisplayContext();
	m_pDisplayContext->Create(g_oTheApp.GetRootTask()->GetRenderInterface(), m_pTextureFactory, m_pFontFactory);
	return TBOOL();
}

// $JPOG: FUNCTION 0067c1f0
TBOOL AGUISystem::OnUpdate(TFLOAT a_fDeltaTime)
{
	return TBOOL();
}

void AGUISystem::UpdateHUDComponets()
{
}

// $JPOG: FUNCTION 0067e3f0
AGUISystem *TOSHI_API AGUISystem::GetGUISystem()
{
	return g_oTheApp.GetRootTask()->GetGUISystem();
}
