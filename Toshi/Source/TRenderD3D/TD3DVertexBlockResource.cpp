#include "TRenderD3D/TD3DVertexBlockResource.h"
#include "TRenderD3D/TD3DVertexPoolResource.h"
#include "TRenderD3D/TD3DVertexFactoryResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>
#include <TRenderD3D/TRenderD3DInterface.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TVertexBlockResource, TResource)
IMPLEMENT_FREELIST(TVertexBlockResource, 0, 8)

// $TRenderD3DInterface: FUNCTION 10008d80
TBOOL TVertexBlockResource::CanFit(TVertexPoolResource *a_pPoolResource)
{
	if (GetFlags() & 1 && a_pPoolResource->GetFlags() & 1) {
		return m_uiMaxVertices >= a_pPoolResource->GetNumVertices() + m_uiVerticesUsed;
	}

	return TFALSE;
}

// $TRenderD3DInterface: FUNCTION 100090e0
void TVertexBlockResource::Unlock()
{
	TASSERT(m_uiLockCount>0);
	if (m_uiLockCount > 0) {
		for (TUINT i = 0; i < m_pFactory->GetVertexFormat()->m_uiNumStreams; i++) {
			HRESULT hRes = m_HALBuffer.apVertexBuffers[i]->Unlock();
			TRenderD3DInterface::TD3DAssert(hRes, "Couldn't unlock stream vertex buffer!");
		}
		m_uiLockCount--;
	}
}

// $TRenderD3DInterface: FUNCTION 10008b00
TBOOL TVertexBlockResource::AttachPool(TVertexPoolResource *a_pPool)
{
	TVALIDADDRESS(a_pPool);

	m_uiVerticesUsed += a_pPool->GetNumVertices();
	a_pPool->SetParent(this);

	if (m_uiFlags & 1) {
		Invalidate();
	}

	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 100088c0
TBOOL TVertexBlockResource::Create(TVertexFactoryResource *a_pFactory, TUSHORT a_uiMaxVertices, TUINT a_uiFlags)
{
	TASSERT(TFALSE == IsCreated());
	TVALIDADDRESS(a_pFactory);
	m_pFactory      = a_pFactory;
	m_uiMaxVertices = a_uiMaxVertices;
	m_uiFlags       = a_uiFlags;
	return TResource::Create();
}
