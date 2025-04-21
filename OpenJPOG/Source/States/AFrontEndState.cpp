#include "AFrontEndState.h"
#include "main.h"
#include "AGameState.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(AFrontendState, ARootState)

void AFrontendState::OnInsertion()
{
	ARootState::OnInsertion();
	if (sm_iFERefCount != 0) {
		sm_iFERefCount++;
		return;
	}
	g_oTheApp.GetRootTask()->LoadFrontEndController();
	sm_iFERefCount = 1;
}

void AFrontendState::OnRemoval()
{
	sm_iFERefCount--;
	if (sm_iFERefCount == 0) {
		g_oTheApp.GetRootTask()->UnloadFrontEndController();
	}
	ARootState::OnRemoval();
}

TBOOL AFrontendState::ParentAllowed(ARootState &a_rParent)
{
	return !a_rParent.IsA(TGetClass(AGameState));
}
