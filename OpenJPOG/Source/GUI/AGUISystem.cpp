#include "AGUISystem.h"
#include "main.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AGUISystem, TTask)

AGUISystem::AGUISystem()
{
	m_pGUIInterface = TNULL;
}

TBOOL AGUISystem::OnCreate()
{
	auto pRenderer = g_oTheApp.GetRootTask()->GetRenderInterface();
	m_pNullResource = (TNullResource*)pRenderer->CreateResource(&TGetClass(TNullResource), TNULL, TNULL);
	m_pGUIInterface->Create();
	return TBOOL();
}

TBOOL AGUISystem::OnUpdate(TFLOAT a_fDeltaTime)
{
	return TBOOL();
}

void AGUISystem::UpdateHUDComponets()
{
}

AGUISystem* TOSHI_API AGUISystem::GetGUISystem()
{
	return g_oTheApp.GetRootTask()->GetGUISystem();
}