#include "TSpriteShader.h"
#include "TRender/TVertexPoolResourceInterface.h"

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

void TSpriteMesh::Unlock(TUSHORT a_iX, TUSHORT a_iY)
{
	TASSERT(m_uiFlags & FLAGS_LOCKED);
	m_uiFlags &= ~FLAGS_LOCKED;
}

TBOOL TSpriteMesh::Lock()
{
	TASSERT(!(m_uiFlags & FLAGS_LOCKED));
	m_uiFlags |= FLAGS_LOCKED;
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
		pMeshes[i].Create(m_uiFlags, m_usMaxStaticIndices, m_usMaxStaticVertices);
		m_aMeshes.InsertTail(*(new TNodeListNodeWrapper<TSpriteMesh>(&pMeshes[i])));
	}
	return TTRUE;
}

void TSpriteShader::SetMaterial(TSpriteMaterial *a_pMaterial)
{
	TIMPLEMENT()
}

void TSpriteShader::SetColour(const TGUIColour &a_rColour)
{
	TIMPLEMENT()
}

void TSpriteShader::BeginMeshGeneration()
{
	m_aMeshes.Head() = m_aMeshes.End();
	m_iNumIndices    = 0;
	m_iNumVertices   = 0;
}

void TSpriteShader::EndMeshGeneration()
{
	if (m_aMeshes.Begin() != m_aMeshes.End()) {
		TSpriteMesh *pMesh = GetMesh();
		pMesh->Unlock(m_iNumVertices, m_iNumIndices);
		if (pMesh->m_bRender) {
			pMesh->Validate();
			pMesh->Render();
		}
	}
}

TOSHI_NAMESPACE_END