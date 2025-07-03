#include "TSpriteShader.h"
#include "TRender/TVertexPoolResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

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
	TIMPLEMENT()
}

void TSpriteShader::EndMeshGeneration()
{
	if (m_aMeshes.Begin() != m_aMeshes.End()) {
		TSpriteMesh *pMesh = GetMesh();
		pMesh->Unlock(m_iHeight, m_iWidth);
		if (false) {
			pMesh->Validate();
		}
	}
	TIMPLEMENT()
}

TOSHI_NAMESPACE_END