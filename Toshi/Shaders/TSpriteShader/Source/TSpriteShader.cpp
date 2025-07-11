#include "TSpriteShader.h"
#include "TRender/TVertexPoolResourceInterface.h"
#include "TRender/TRenderInterface.h"
#include <TRenderD3D/TD3DVertexPoolResource.h>

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TSpriteMesh, TMesh)

TBOOL TSpriteMesh::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}
	if (m_pVertexPool && m_pIndexPool) {
		m_pVertexPool->Validate();
		m_pIndexPool->Validate();
		return Validate();
	}
	return TFALSE;
}

void TSpriteMesh::Unlock(TUSHORT a_usNumVertices, TUSHORT a_usNumIndices)
{
	TASSERT(m_uiFlags&FLAGS_LOCKED);
	m_iDeltaNumVertices = a_usNumVertices - m_iNumVertices;
	m_iDeltaNumIndices  = a_usNumIndices - m_iNumIndices;
	m_uiFlags &= ~FLAGS_LOCKED;
}

TBOOL TSpriteMesh::Lock()
{
	TASSERT(!(m_uiFlags&FLAGS_LOCKED));
	m_uiFlags |= FLAGS_LOCKED;
	TSpriteShader *pShader = static_cast<TSpriteShader *>(GetShader());
	m_iNumVertices         = pShader->GetNumVertices();
	m_iNumIndices          = pShader->GetNumIndices();
	return TTRUE;
}

IMPLEMENT_DYNAMIC(TSpriteMaterial, TMaterial)

IMPLEMENT_DYNAMIC(TSpriteShader, TShader)

TBOOL TSpriteShader::Create()
{
	if (!TShader::Create()) {
		return TFALSE;
	}
	TINT iMeshSize;
	TSpriteMesh *pMeshes = CreateMesh(256, iMeshSize);
	for (size_t i = 0; i < 256; i++) {
		pMeshes[i].Create(m_uiFlags, m_usMaxStaticVertices, m_usMaxStaticIndices);
		m_aMeshes.InsertTail(*(new TNodeWrapper<TSpriteMesh>(&pMeshes[i])));
	}
	return TTRUE;
}

void TSpriteShader::SetMaterial(TSpriteMaterial *a_pMaterial)
{
	if (m_pMaterial != a_pMaterial) {
		m_pMaterial = a_pMaterial;
	}
}

void TSpriteShader::SetColour(const TGUIColour &a_rColour)
{
	TIMPLEMENT()
}

void TSpriteShader::BeginMeshGeneration()
{
	m_pCurrentMesh = m_aMeshes.End();
	m_iNumIndices  = 0;
	m_iNumVertices = 0;
}

void TSpriteShader::EndMeshGeneration()
{
	if (m_pCurrentMesh != m_aMeshes.End()) {
		TSpriteMesh *pMesh = GetMesh();
		pMesh->Unlock(m_iNumVertices, m_iNumIndices);
		if (pMesh->m_iDeltaNumIndices) {
			pMesh->Validate();
			pMesh->Render();
		}
	}
}

void TSpriteShader::RenderTriStrip(TFLOAT pos1x, TFLOAT pos1y, TFLOAT pos2x, TFLOAT pos2y, TFLOAT a_fZ, TFLOAT uv1x, TFLOAT uv1y, TFLOAT uv2x, TFLOAT uv2y)
{
	TSpriteMesh *pMesh = FUN_10001ad0(4, 6);
	if (!pMesh) {
		return;
	}
	TUSHORT iVertices = m_iNumVertices;
	TUSHORT iIndices  = (pMesh->m_iNumIndices == m_iNumIndices) ? 4 : 6;
	TINT    color     = m_colorR << 0x18 | m_colorG << 0x10 | m_colorB << 0x8 | m_colorA;

	m_aVertices[iVertices].Position = { pos1x, pos1y, a_fZ };
	m_aVertices[iVertices].Colour   = color;
	m_aVertices[iVertices].UV       = { uv1x, uv1y };
	iVertices++;
	m_aVertices[iVertices].Position = { pos1x, pos2y, a_fZ };
	m_aVertices[iVertices].Colour   = color;
	m_aVertices[iVertices].UV       = { uv1x, uv2y };
	iVertices++;
	m_aVertices[iVertices].Position = { pos2x, pos1y, a_fZ };
	m_aVertices[iVertices].Colour   = color;
	m_aVertices[iVertices].UV       = { uv2x, uv1y };
	iVertices++;
	m_aVertices[iVertices].Position = { pos2x, pos2y, a_fZ };
	m_aVertices[iVertices].Colour   = color;
	m_aVertices[iVertices].UV       = { uv2x, uv2y };

	m_iNumVertices += 4;
	m_iNumIndices += iIndices;

	TIMPLEMENT();
}

TSpriteMesh *TSpriteShader::FUN_10001ad0(TUSHORT a_iNumVertices, TUSHORT a_iNumIndices)
{
	if ((m_iNumVertices + a_iNumVertices >= m_usMaxStaticVertices) || 
		(m_iNumIndices + a_iNumIndices >= m_usMaxStaticIndices)) {
		return TNULL;
	}
	if (m_pCurrentMesh == m_aMeshes.End()) {
		FUN_100019e0();
	}
	else if (m_bForceRender) {
		FUN_100019e0();
		m_bForceRender = TFALSE;
	}
	if (m_pMaterial != GetMesh()->GetMaterial()) {
		FUN_100019e0();
	}
	return GetMesh();
}

void TSpriteShader::FUN_100019e0()
{
	EndMeshGeneration();
	if (m_pCurrentMesh) {
		m_pCurrentMesh = m_pCurrentMesh->Next();
	}
	if (m_pCurrentMesh == m_aMeshes.End()) {
		FUN_10001b60();
		m_pCurrentMesh = m_aMeshes.Tail();
	}
	TSpriteMesh *pMesh = GetMesh();
	pMesh->SetMaterial(m_pMaterial);
	pMesh->m_vPos1 = m_vPos1;
	pMesh->m_vPos2 = m_vPos2;
	pMesh->m_vUV1 = m_vUV1;
	pMesh->m_vUV2 = m_vUV2;
	pMesh->Lock();
	GetRenderer()->GetCurrentRenderContext()->SetModelViewMatrix(m_oModelViewMatrix);
}

void TSpriteShader::FUN_10001b60()
{
	TSpriteMesh *pMesh = CreateMesh(TNULL);
	pMesh->Create(m_uiFlags, m_usMaxStaticVertices, m_usMaxStaticIndices);
	m_aMeshes.InsertTail(*(new TNodeWrapper<TSpriteMesh>(pMesh)));
}

TOSHI_NAMESPACE_END