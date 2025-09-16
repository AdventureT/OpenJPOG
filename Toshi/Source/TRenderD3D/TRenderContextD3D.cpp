#include "TRenderD3D/TRenderContextD3D.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

void TRenderContextD3D::ComputePerspectiveFrustum()
{
	PROJECTIONPARAMS oProjectionParams = GetProjectionParameters();
	TFLOAT           fVal1             = 1.0f / oProjectionParams.m_oProj(0);
	TIMPLEMENT();
}

TOSHI_NAMESPACE_END