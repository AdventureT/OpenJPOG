#include "TRenderD3D/TRenderD3DInterface.h"
#include <dxerr8.h>

TOSHI_NAMESPACE_USING

void TOSHI_API TRenderD3DInterface::TD3DAssert(HRESULT a_hr, TPCCHAR a_pError)
{
	if (FAILED(a_hr)) {
		TCString errmsg;
		if (a_pError == TNULL) {
			a_pError = "D3D Error";
		}
		errmsg.Format("> %s: D3D Error [%s] : Description [%s] !\n", a_pError, DXGetErrorString8(a_hr), DXGetErrorDescription8(a_hr));
		OutputDebugString(errmsg);
		TASSERT(SUCCEEDED(a_hr));
	}
}
