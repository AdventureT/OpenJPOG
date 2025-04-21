#include "D3D/TSpriteShaderD3D.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_BEGIN

void TSpriteMaterialHAL::PreRender()
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8    *pDevice   = pRenderer->GetD3DDevice();
	if (m_pTexture) {
		m_pTexture->Validate();
		if (m_pTexture->GetD3DTexture()) {
			pDevice->SetTexture(0, m_pTexture->GetD3DTexture());
			pRenderer->SetTextureAddressMode(0, m_pTexture->GetAddressMode());
		}
	}
	else {
		pDevice->SetTexture(0, TNULL);
	}
}

void TSpriteMaterialHAL::PostRender()
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8    *pDevice   = pRenderer->GetD3DDevice();
	if (m_Flags & FLAGS_VALID) {
		pDevice->SetRenderState(D3DRS_CULLMODE, 2);
	}
	pRenderer->SetTextureAddressMode(0, TTextureResource::ADDRESSMODE_WRAP);
	pDevice->SetTexture(0, TNULL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

TOSHI_NAMESPACE_END
