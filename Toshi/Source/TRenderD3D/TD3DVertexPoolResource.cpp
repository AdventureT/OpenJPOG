#include "TRenderD3D/TD3DVertexPoolResource.h"
#include "TRenderD3D/TD3DVertexBlockResource.h"
#include "TRenderD3D/TD3DVertexFactoryResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TVertexPoolResource, TVertexPoolResourceInterface)

// $TRenderD3DInterface: FUNCTION 10009af0
TBOOL TVertexPoolResource::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}

	TVertexFactoryResource *pFactory     = TSTATICCAST(TVertexFactoryResource *, GetFactory());
	TVertexBlockResource   *pVertexBlock = pFactory->FindBlockResource(this);

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
			uiFlags    = 2;
		}
		else {
			if (uiUnk1 != 4) {
				return TFALSE;
			}

			uiNumVerts = GetMaxVertices();
			uiFlags    = 4;
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

// $TRenderD3DInterface: FUNCTION 10009c30
void TVertexPoolResource::Invalidate()
{
}

// $TRenderD3DInterface: FUNCTION 1000a500
void TVertexPoolResource::OnDestroy()
{
}

// $TRenderD3DInterface: FUNCTION 10009cd0
TBOOL TVertexPoolResource::Lock(LockBuffer *a_pLockBuffer)
{
	TVALIDADDRESS(a_pLockBuffer);
	return TBOOL();
}

// $TRenderD3DInterface: FUNCTION 10009f60
void TVertexPoolResource::Unlock(TUSHORT a_uiNewNumVertices)
{
	TASSERT(m_uiLockCount > 0);
	if (m_uiLockCount > 0 && --m_uiLockCount == 0) {
		TINT iChange = a_uiNewNumVertices - GetNumVertices();
		if (iChange != 0) {
			if (GetParent()) {
				if (GetParent()->GetClass().IsA(TGetClass(TVertexBlockResource))) {
					TVertexBlockResource *pVertexBlock = static_cast<TVertexBlockResource *>(Parent());
					pVertexBlock->ChildVertexUsedChanged(iChange);
				}
			}
		}
		m_usNumVertices = a_uiNewNumVertices;
		if (!(GetFlags() & 6)) {
			if (GetFlags() & 1) {
				Validate();
			}
		}
		else {
			GetVertexBlock()->Unlock();
		}
	}
}

// $TRenderD3DInterface: FUNCTION 1000a3c0
TBOOL TVertexPoolResource::Create(TVertexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags)
{
	return TBOOL();
}
