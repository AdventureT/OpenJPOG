#include "AGUISystem.h"
#include "main.h"

AGUISystem* TOSHI_API AGUISystem::GetGUISystem()
{
	return g_oTheApp.GetRootTask()->GetGUISystem();
}
