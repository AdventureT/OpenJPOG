#pragma once
#include "TKernel/TDebug.h"
#include "TRender/TRenderInterface.h"
#include <d3d8.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TRenderD3DInterface : public TRenderInterface
{
public:
	static void TOSHI_API TD3DAssert(HRESULT a_hr, TPCCHAR a_pError);

	IDirect3DDevice8* GetD3DDevice() { return m_pD3DDevice; }

private:
	IDirect3DDevice8* m_pD3DDevice; // 0x180
};

TOSHI_NAMESPACE_END