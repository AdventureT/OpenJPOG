#include "AGUISystem.h"
#include "main.h"


TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AGUISystem, TTask)

void AGUISystem::UpdateHUDComponets()
{
}

AGUISystem* TOSHI_API AGUISystem::GetGUISystem()
{
	return g_oTheApp.GetRootTask()->GetGUISystem();
}