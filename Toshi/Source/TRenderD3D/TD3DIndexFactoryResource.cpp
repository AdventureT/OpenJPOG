#include "TRenderD3D/TD3DIndexFactoryResource.h"
#include "TRender/TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNCREATE(TIndexFactoryResource, TIndexFactoryResourceInterface)

TIndexPoolResourceInterface *TIndexFactoryResource::CreatePoolResource(TUINT16 a_uiMaxStaticIndices, TUINT16 a_uiFlags)
{
	TIndexPoolResource *pVertexPool = TSTATICCAST(
		TIndexPoolResource *,
		GetRenderer()->CreateResource(&TGetClass(TIndexPoolResource), TNULL, this));

	TVALIDADDRESS(pVertexPool);

	pVertexPool->Create(this, a_uiMaxStaticIndices, a_uiFlags);
	CreatePool(a_uiMaxStaticIndices, a_uiFlags);
	return pVertexPool;
}

struct CallbackStruct
{
	TIndexBlockResource *m_pBlock;
	TIndexPoolResource  *m_pPool;
};

// $TRenderD3DInterface: FUNCTION 1000b470
static TBOOL CallBack(TResource *a_pResource, TPVOID a_pUserData)
{
	CallbackStruct      *pStruct        = TSTATICCAST(CallbackStruct *, a_pUserData);
	TIndexBlockResource *pBlockResource = TSTATICCAST(TIndexBlockResource *, a_pResource);
	if (a_pResource->IsExactly(TGetClass(TIndexBlockResource))) {
		if (pBlockResource->CanFit(pStruct->m_pPool) && !pBlockResource->IsDying()) {
			pStruct->m_pBlock = pBlockResource;
			return TFALSE;
		}
	}
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000b730
TIndexBlockResource *TIndexFactoryResource::FindBlockResource(TIndexPoolResource *a_pResource)
{
	if (a_pResource->GetFlags() & 2) {
		return TNULL;
	}
	CallbackStruct result = { TNULL, a_pResource };
	RecurseSimple(CallBack, this, &result);
	return result.m_pBlock;
}

TIndexBlockResource *TIndexFactoryResource::CreateBlockResource(TUINT16 a_uiMaxIndices, TUINT32 a_uiFlags)
{
	TIndexBlockResource *pIndexBlock = TSTATICCAST(
		TIndexBlockResource *,
		GetRenderer()->CreateResource(&TGetClass(TIndexBlockResource), TNULL, this));

	TVALIDADDRESS(pIndexBlock);

	pIndexBlock->Create(this, a_uiMaxIndices, a_uiFlags);
	return pIndexBlock;
}

TOSHI_NAMESPACE_END