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
	a_pLockBuffer->m_uiNumStreams        = vertexFormat->m_uiNumStreams;
	DWORD uiFlags;
	TUINT uiNumVertices = 0;
	TUINT uiUnk1        = m_uiFlags & 7;
	if (uiUnk1 == 1) {
		uiFlags                 = D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->m_uiStartVertex = 0;
	}
	else if (uiUnk1 == 2) {
		Validate();
		uiFlags                 = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->m_uiStartVertex = 0;
	}
	else if (uiUnk1 == 4) {
		TASSERT(m_uiLockCount==0);
		Validate();
		uiNumVertices = a_usNumVertices;
		if (m_uiMaxVertices < m_uiOffset + uiNumVertices) {
			uiFlags                 = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->m_uiStartVertex = 0;
			m_uiOffset              = uiNumVertices;
		}
		else {
			uiFlags                 = D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->m_uiStartVertex = m_uiOffset;
			m_uiOffset += uiNumVertices;
		}
	}
	for (TUINT i = 0; i < a_pLockBuffer->m_uiNumStreams; i++) {
		HRESULT hRes = m_HALBuffer.apVertexBuffers[i]->Lock(
			a_pLockBuffer->m_uiStartVertex * vertexFormat->m_aStreamFormats[i].m_uiVertexSize,
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

TBOOL TVertexBlockResource::DetachPool(TVertexPoolResource *a_pPool)
{
	TVALIDADDRESS(a_pPool);
	TASSERT(a_pPool->Parent()==this);
	TResource *pVertexFactory = Parent();
	TASSERT(TTRUE==pVertexFactory->GetClass().IsExactly(TGetClass(TVertexFactoryResource)));
	a_pPool->SetParent(pVertexFactory);
	TASSERT(m_uiVerticesUsed >= a_pPool->GetNumVertices());
	m_uiVerticesUsed -= a_pPool->GetNumVertices();
	if (m_uiVerticesUsed == 0 && Child() == TNULL) {
		GetRenderer()->DestroyResource(this);
		return TTRUE;
	}
	TASSERT(Child() != TNULL);
	return TFALSE;
}

struct CallbackStruct
{
	TVertexBlockResource                    *m_pVertexBlock;   // 0x0
	TVertexPoolResourceInterface::LockBuffer m_oHALStaticLock; // 0x4
};

// $TRenderD3DInterface: FUNCTION 100086c0
static TBOOL CallBack(TResource *a_pResource, TPVOID a_pUserData)
{
	CallbackStruct      *pData = TSTATICCAST(CallbackStruct *, a_pUserData);
	TVertexPoolResource *pPool   = TSTATICCAST(TVertexPoolResource *, a_pResource);
	if (!a_pResource->IsExactly(TGetClass(TVertexPoolResource))) {
		return TTRUE;
	}
	if (!(pPool->GetFlags() & 1)) {
		return TTRUE;
	}
	TVertexFactoryResource *pFactory     = TSTATICCAST(TVertexFactoryResource *, pPool->GetFactory());
	TVertexFactoryFormat   *vertexFormat = pFactory->GetVertexFormat();
	pPool->m_uiVertexOffset              = pData->m_oHALStaticLock.m_uiStartVertex;
	pData->m_oHALStaticLock.m_uiStartVertex += pPool->GetNumVertices();
	TASSERT(pData->m_oHALStaticLock.m_uiStartVertex <= pData->m_pVertexBlock->GetMaxVertices());
	for (TUINT i = 0; i < vertexFormat->GetNumStreams(); i++) {
		TUSHORT uiVertexSize = vertexFormat->m_aStreamFormats[i].m_uiVertexSize;
		TSystem::MemCopy(
			pData->m_oHALStaticLock.apStreams[i] + pPool->m_uiVertexOffset * uiVertexSize,
			pPool->GetManagedStream(i),
			pPool->GetNumVertices() * uiVertexSize);
	}
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 10008960
TBOOL TVertexBlockResource::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}
	TASSERT(TTRUE==Parent()->GetClass().IsExactly(TGetClass(TVertexFactoryResource)));
	if (!CreateHAL()) {
		return TFALSE;
	}
	if (GetFlags() & 1) {
		CallbackStruct oData;
		if (Lock(&oData.m_oHALStaticLock, 0)) {
			RecurseSimple(CallBack, this, &oData);
			Unlock();
		}
	}
	return TResource::Validate();
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

// $TRenderD3DInterface: FUNCTION 100091a0
TBOOL TVertexBlockResource::CreateHAL()
{
	DestroyHAL();
	TRenderD3DInterface  *pRenderer    = static_cast<TRenderD3DInterface *>(GetRenderer());
	TVertexFactoryFormat *vertexFormat = GetFactory()->GetVertexFormat();
	m_HALBuffer.uiNumStreams           = vertexFormat->m_uiNumStreams;
	for (TUINT i = 0; i < m_HALBuffer.uiNumStreams; i++) {
		UINT  length = vertexFormat->m_aStreamFormats[i].m_uiVertexSize * m_uiMaxVertices;
		DWORD usage  = D3DUSAGE_WRITEONLY;
		if (GetFlags() & 1) {
			usage      = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
			m_uiOffset = 0;
		}
		if (!pRenderer->GetCurrentDevice()->SupportsHardwareTransfomations()) {
			usage |= D3DUSAGE_SOFTWAREPROCESSING;
		}
		HRESULT hRes = pRenderer->GetD3DDevice()->CreateVertexBuffer(
			length,
			usage,
			0,
			D3DPOOL_DEFAULT,
			&m_HALBuffer.apVertexBuffers[i]);
		TRenderD3DInterface::TD3DAssert(hRes, "Unable to create a new vertex buffer!");
		
		TMemory::HALMemInfo memInfoHAL;
		TMemory::GetHALMemInfo(memInfoHAL);
		s_iHALMemoryUsage += memInfoHAL.m_iMemUsage;
		s_iCurrentNumHALCreated += 1;
		s_iTotalNumHALCreated += 1;
		s_iTotalVertexBufferBytesAllocated += length;
		s_iCurrentVertexBufferBytesAllocated += length;

		if (s_iTotalVertexBufferBytesAllocated < s_iHALMemoryUsage) {
			s_iWastedVertexBufferBytesAllocated = s_iHALMemoryUsage - s_iTotalVertexBufferBytesAllocated;
		}
	}

	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 10009300
void TVertexBlockResource::DestroyHAL()
{
	TMemory::HALMemInfo memInfoHAL;
	TMemory::GetHALMemInfo(memInfoHAL);
	for (TUINT i = 0; i < m_HALBuffer.uiNumStreams; i++) {
		if (m_HALBuffer.apVertexBuffers[i]) {
			TD3DRELEASE(m_HALBuffer.apVertexBuffers[i]);
			m_HALBuffer.apVertexBuffers[i] = TNULL;
			s_iCurrentNumHALCreated--;
			s_iTotalNumHALDestroyed++;
			s_iCurrentVertexBufferBytesAllocated -= GetFactory()->GetVertexFormat()->m_aStreamFormats[i].m_uiVertexSize * m_uiMaxVertices;
		}
	}
	m_HALBuffer.uiNumStreams = 0;
	TMemory::GetHALMemInfo(memInfoHAL);
	s_iHALMemoryUsage = s_iHALMemoryUsage - memInfoHAL.m_iMemUsage;
	if (s_iTotalVertexBufferBytesAllocated < s_iHALMemoryUsage) {
		s_iWastedVertexBufferBytesAllocated = s_iHALMemoryUsage - s_iTotalVertexBufferBytesAllocated;
	}
}
