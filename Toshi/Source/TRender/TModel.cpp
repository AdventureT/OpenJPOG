#include "TModel.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TMesh, TResource)

TBOOL TMesh::Render()
{
	static const TBOOL s_bEnableRender = TTRUE;
	return s_bEnableRender;
}
