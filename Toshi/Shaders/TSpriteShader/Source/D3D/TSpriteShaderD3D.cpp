#include "D3D/TSpriteShaderD3D.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TD3DVertexFactoryResource.h"

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
	TTextureResourceHAL *pResource = static_cast<TTextureResourceHAL *>(m_pTexture);
	if (pResource) {
		pResource->Validate();
		if (pResource->GetD3DTexture()) {
			pDevice->SetTexture(0, pResource->GetD3DTexture());
			pRenderer->SetTextureAddressMode(0, pResource->GetAddressMode());
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

void TSpriteShaderOrderTable::Render()
{
	for (TINT i = 0; i < m_uiNumRendPackets; i++) {
		m_pShader->Render(&m_pRenderPackets[i]);
	}
	m_uiNumRendPackets = 0;
}

TRenderPacket *TSpriteShaderOrderTable::AllocRenderPacket()
{
	m_uiNumRendPackets++;
	if (m_uiNumRendPackets == m_uiMaxRendPackets) {
		return TNULL;
	}
	return &m_pRenderPackets[m_uiNumRendPackets];
}

IMPLEMENT_DYNCREATE(TSpriteShaderHAL, TSpriteShader)

const DWORD TSpriteShaderHAL::SHADERDECL[] = {
	0x20000000, 0x40020000, 0x40040001, 0x40010002, 0xFFFFFFFFF
};

TBOOL TSpriteShaderHAL::Create()
{
	OnResetDevice();
	if (!TSpriteShader::Create()) {
		return TFALSE;
	}
	m_pLineMaterial = CreateMaterial("LineMat");
	m_pLineMaterial->SetBlendMode2(1);
	m_pLineMaterial->SetBlendMode(1);
	m_pFillMaterial = CreateMaterial("FillMat");
	m_pLineMaterial->SetBlendMode(1);
	return TTRUE;
}

TSpriteMaterial *TSpriteShaderHAL::CreateMaterial(TPCCHAR a_szName)
{
	Validate();
	TSpriteMaterial *pMaterial = static_cast<TSpriteMaterial *>(GetRenderer()->CreateResource(&TGetClass(TSpriteMaterialHAL), a_szName, this));
	pMaterial->SetShader(this);
	pMaterial->SetFlag(1, TTRUE);
	return pMaterial;
}

TSpriteMesh *TSpriteShaderHAL::CreateMesh(TINT a_iCount, TINT &a_rMeshSize)
{
	TSpriteMeshHAL *pMeshes = new TSpriteMeshHAL[a_iCount];
	for (TINT i = 0; i < a_iCount; i++) {
		TSpriteMeshHAL *pMesh = static_cast<TSpriteMeshHAL *>(GetRenderer()->CreateResourceInPlace(&TGetClass(TSpriteMeshHAL), &pMeshes[i], TNULL, this));
		pMesh->SetShader(this);
	}
	a_rMeshSize = sizeof(TSpriteMeshHAL);
	return pMeshes;
}

TBOOL TSpriteShaderHAL::OnResetDevice()
{
	TVertexFactoryResource *pVertexFactory = static_cast<TVertexFactoryResource *>(GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_VFSYSSVNDUV1));
	TUINT                   uiFlags = 0;
	if ((m_uiFlags & 1) != 0) {
		uiFlags = 1;
	}
	else if ((m_uiFlags & 2) != 0) {
		uiFlags = 2;
	}
	else if ((m_uiFlags & 4) != 0) {
		uiFlags = 4;
	}
	m_pVertexPool = static_cast<TVertexPoolResource *>(pVertexFactory->CreatePoolResource(m_usMaxStaticVertices, uiFlags));
	// Same with IndexPool
	TIMPLEMENT();
	for (auto it = m_aMeshes.Begin(); it != m_aMeshes.End(); it++) {
		it->Get()->SetVertexPool(m_pVertexPool);
		// Same with IndexPool
	}
	Validate();
	return TTRUE;
}

void TSpriteShaderHAL::Flush()
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8 *pDevice = pRenderer->GetD3DDevice();
	HRESULT hRes = pDevice->SetVertexShader(GetVertexShaderHandle());
	TRenderD3DInterface::TD3DAssert(hRes, TNULL);
	pDevice->SetPixelShader(0);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CURRENT);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	if (m_bMipMapLODBias) {
		pDevice->SetTextureStageState(0, D3DTSS_MIPMAPLODBIAS, 0xC0000000);
	}
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_oOrderTable.Render();
	if (m_bMipMapLODBias) {
		pDevice->SetTextureStageState(0, D3DTSS_MIPMAPLODBIAS, 0);
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void TSpriteShaderHAL::Render(TRenderPacket *a_pRenderPacket)
{
	TRenderD3DInterface *pRenderer = GetRenderer();
	IDirect3DDevice8    *pDevice   = pRenderer->GetD3DDevice();
	/*TMesh *pMesh = a_pRenderPacket->GetMesh();
	if (pMesh->IsDying()) {
		return;
	}*/
	TIMPLEMENT();
}

TBOOL TSpriteShaderHAL::SupportMipMapLODBias()
{
	TRenderD3DInterface *pRenderer  = GetRenderer();
	IDirect3DDevice8    *pDevice    = pRenderer->GetD3DDevice();
	D3DCAPS8             caps;
	if (pDevice) {
		pDevice->GetDeviceCaps(&caps);
	}
	else {
		IDirect3D8 *pInterface = pRenderer->GetD3DInterface();
		if (!pInterface) {
			return TFALSE;
		}
		pInterface->GetDeviceCaps(0, D3DDEVTYPE_HAL, &caps);
	}
	return (caps.DevCaps & D3DDEVCAPS_DRAWPRIMITIVES2) != 0;
}

static const char VERTEXSHADER[] = {
	0x00, 0x01, 0xFE, 0xFF, 0xFE, 0xFF, 0x09, 0x00, 0x44, 0x33, 0x44, 0x58, 0x38, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x41, 0x73, 0x73, 0x65, 0x6D, 0x62, 0x6C, 0x65, 0x72, 0x20, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x30, 0x2E, 0x39, 0x31, 0x00, 0xFE, 0xFF, 0x07, 0x00, 0x46, 0x49, 0x4C, 0x45, 0x54, 0x53, 0x70, 0x72, 0x69, 0x74, 0x65, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x44, 0x33, 0x44, 0x2E, 0x76, 0x73, 0x68, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x02, 0x00, 0x4C, 0x49, 0x4E, 0x45, 0x12, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0xE4, 0x90, 0x00, 0x00, 0xE4, 0xA0, 0xFE, 0xFF, 0x02, 0x00, 0x4C, 0x49, 0x4E, 0x45, 0x13, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xD0, 0x01, 0x00, 0xE4, 0x90, 0x04, 0x00, 0xE4, 0xA0, 0xFE, 0xFF, 0x02, 0x00, 0x4C, 0x49, 0x4E, 0x45, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x02, 0x00, 0xE4, 0x90, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x33, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

TBOOL TSpriteShaderHAL::Validate()
{
	if (TResource::IsValid()) {
		return TTRUE;
	}
	TASSERT(INVALIDSHADERHANDLE==m_dwVertexShaderHandle)
	m_bMipMapLODBias          = SupportMipMapLODBias();
	IDirect3DDevice8 *pDevice = GetRenderer()->GetD3DDevice();
	if (!pDevice) {
		return TFALSE;
	}
	HRESULT res = pDevice->CreateVertexShader(SHADERDECL, (DWORD *)VERTEXSHADER, &m_dwVertexShaderHandle, 0);
	if (FAILED(res)) {
		m_dwVertexShaderHandle = 0x142;
	}
	return TResource::Validate();
}

void TSpriteShaderHAL::BeginMeshGeneration()
{
	m_pVertexPool->Lock(m_pVertexLockBuffer);
	TSpriteShader::BeginMeshGeneration();
}

void TSpriteShaderHAL::EndMeshGeneration()
{
	TSpriteShader::EndMeshGeneration();
	m_pVertexPool->Unlock(m_iNumVertices);
}

IMPLEMENT_DYNCREATE(TSpriteMeshHAL, TSpriteMesh)

TBOOL TSpriteMeshHAL::Create(TUINT a_uiFlags, TUSHORT a_usX, TUSHORT a_usY)
{
	m_uiFlags = a_uiFlags;
	m_pVertexPool = GetShader()->GetVertexPool();
	//m_pIndexPool = GetShader()->GetIndexPool();
	return TResource::Create();
}

TBOOL TSpriteMeshHAL::Render()
{
	if (!TMesh::Render()) {
		return TFALSE;
	}
	TRenderInterface *pRenderer = GetRenderer();
	TRenderContext *pContext = pRenderer->GetCurrentRenderContext();
	return TBOOL();
}

TOSHI_NAMESPACE_END
