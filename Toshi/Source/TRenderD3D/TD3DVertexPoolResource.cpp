#include "TRenderD3D/TD3DVertexPoolResource.h"
#include "TRenderD3D/TD3DVertexBlockResource.h"
#include "TRenderD3D/TD3DVertexFactoryResource.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TVertexPoolResource, TVertexPoolResourceInterface)

TBOOL TVertexPoolResource::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}

	TVertexFactoryResource* pFactory = TSTATICCAST(TVertexFactoryResource*, GetFactory());
	TVertexBlockResource* pVertexBlock = pFactory->FindBlockResource(this);

	if (!pVertexBlock)
	{
		TUINT32 uiFlags;
		TUSHORT uiNumVerts;

		TUINT8 uiUnk1 = GetFlags() & 7;

		if (uiUnk1 == 1) {
			uiNumVerts = pFactory->GetMaxStaticVertices();
			TASSERT(GetNumVertices() <= uiNumVerts);
			uiFlags = 1;
		}
		else if (uiUnk1 == 2) {
			uiNumVerts = GetMaxVertices();
			uiFlags = 2;
		}
		else {
			if (uiUnk1 != 4) {
				return TFALSE;
			}

			uiNumVerts = GetMaxVertices();
			uiFlags = 4;
		}

		pVertexBlock = pFactory->CreateBlockResource(uiNumVerts, uiFlags);
		TVALIDADDRESS(pVertexBlock);

		if (!pVertexBlock) {
			return TFALSE;
		}
	}

	pVertexBlock->AttachPool(this);
	return TResource::Validate();
}

void TVertexPoolResource::Invalidate()
{
}

void TVertexPoolResource::OnDestroy()
{
}

TBOOL TVertexPoolResource::Lock(LockBuffer* a_pLockBuffer)
{
	return TBOOL();
}

void TVertexPoolResource::Unlock(TUSHORT a_uiNewNumVertices)
{
}

TBOOL TVertexPoolResource::Create(TVertexFactoryResourceInterface* a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags)
{
	return TBOOL();
}
