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

TBOOL TVertexBlockResource::Lock(TVertexPoolResourceInterface::LockBuffer *a_pLockBuffer, TUSHORT a_usNumVertices)
{
	TVALIDADDRESS(a_pLockBuffer);
	TVertexFactoryFormat *vertexFormat = GetFactory()->GetVertexFormat();
	a_pLockBuffer->uiNumStreams        = vertexFormat->m_uiNumStreams;
	DWORD uiFlags;
	TUINT uiNumVertices = 0;
	TUINT uiUnk1        = m_uiFlags & 7;
	if (uiUnk1 == 1) {
		uiFlags                 = D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->uiOffset = 0;
	}
	else if (uiUnk1 == 2) {
		Validate();
		uiFlags                 = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->uiOffset = 0;
	}
	else if (uiUnk1 == 4) {
		TASSERT(m_uiLockCount==0);
		Validate();
		uiNumVertices = a_usNumVertices;
		if (m_uiMaxVertices < m_uiOffset + uiNumVertices) {
			uiFlags                 = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->uiOffset = 0;
			m_uiOffset              = uiNumVertices;
		}
		else {
			uiFlags                 = D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->uiOffset = m_uiOffset;
			m_uiOffset += uiNumVertices;
		}
	}
	for (TUINT i = 0; i < a_pLockBuffer->uiNumStreams; i++) {
		HRESULT hRes = m_HALBuffer.apVertexBuffers[i]->Lock(
			a_pLockBuffer->uiOffset * vertexFormat->m_aStreamFormats[i].m_uiVertexSize,
			uiNumVertices * vertexFormat->m_aStreamFormats[i].m_uiVertexSize,
			&a_pLockBuffer->apStreams[i],
			uiFlags);
		TRenderD3DInterface::TD3DAssert(hRes, "Couldn't lock stream vertex buffer");
	}
	m_uiLockCount++;
	return TTRUE;
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
	if (GetFlags() & 1) {
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
