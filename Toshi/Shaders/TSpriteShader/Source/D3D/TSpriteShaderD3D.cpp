#include "D3D/TSpriteShaderD3D.h"
#include "TRenderD3D/TRenderD3DInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNCREATE(TSpriteMaterialHAL, TSpriteMaterial)

void TSpriteMaterialHAL::PreRender()
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8    *pDevice   = pRenderer->GetD3DDevice();
	if (m_pTexture) {
		m_pTexture[0]->Validate();
		if (m_pTexture[0]->GetD3DTexture()) {
			pDevice->SetTexture(0, m_pTexture[0]->GetD3DTexture());
			pRenderer->SetTextureAddressMode(0, m_pTexture[0]->GetAddressMode());
		}
	}
	else {
		pDevice->SetTexture(0, TNULL);
	}
	if (m_Flags & FLAGS_VALID) {
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}
	switch (m_eBlendMode)
	{
		case 0:
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			break;
		case 1:
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			break;
		case 2:
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			break;
		case 3:
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			break;
		case 6:
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			break;
	}
}

void TSpriteMaterialHAL::PostRender()
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8    *pDevice   = pRenderer->GetD3DDevice();
	if (m_Flags & FLAGS_VALID) {
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}
	pRenderer->SetTextureAddressMode(0, TTextureResource::ADDRESSMODE_WRAP);
	pDevice->SetTexture(0, TNULL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

TOSHI_NAMESPACE_END
