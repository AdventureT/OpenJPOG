#include "TRenderD3D/TD3DVertexFactoryResource.h"
#include "TRender/TRenderInterface.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TVertexFactoryResource, TVertexFactoryResourceInterface)

TVertexPoolResourceInterface* TVertexFactoryResource::CreatePoolResource(TUSHORT a_uiMaxStaticVertices, TUINT a_uiFlags)
{
	TVertexPoolResource* pVertexPool = TSTATICCAST(
		TVertexPoolResource*,
		GetRenderer()->CreateResource(&TGetClass(TVertexPoolResource), TNULL, this)
	);

	TVALIDADDRESS(pVertexPool);

	pVertexPool->Create(this, a_uiMaxStaticVertices, a_uiFlags);
	CreatePool(a_uiMaxStaticVertices, a_uiFlags);
	return pVertexPool;
}

struct CallbackStruct
{
	TVertexBlockResource* m_pBlock;
	TVertexPoolResource*  m_pPool;
};

static TBOOL CallBack(TResource* a_pResource, TPVOID a_pUserData)
{
	CallbackStruct* pStruct = TSTATICCAST(CallbackStruct*, a_pUserData);
	TVertexBlockResource* pBlockResource = TSTATICCAST(TVertexBlockResource*, a_pResource);

	if (a_pResource->IsA(TGetClass(TVertexBlockResource))) {

		if (pBlockResource->CanFit(pStruct->m_pPool) && !pBlockResource->IsDying()) {
			pStruct->m_pBlock = pBlockResource;
			return TFALSE;
		}
	}

	return TTRUE;
}

TVertexBlockResource* TVertexFactoryResource::FindBlockResource(TVertexPoolResource* a_pResource)
{
	CallbackStruct result = { TNULL, a_pResource };
	if (a_pResource->GetFlags() & 2) {
		return TNULL;
	}
	RecurseSimple(CallBack, this, &result);
}

TVertexBlockResource* TVertexFactoryResource::CreateBlockResource(TUSHORT a_uiMaxVertices, TUINT a_uiFlags)
{
	TVertexBlockResource* pVertexBlock = TSTATICCAST(
		TVertexBlockResource*,
		GetRenderer()->CreateResource(&TGetClass(TVertexBlockResource), TNULL, this)
	);

	TVALIDADDRESS(pVertexBlock);

	pVertexBlock->Create(this, a_uiMaxVertices, a_uiFlags);
	return pVertexBlock;
}
