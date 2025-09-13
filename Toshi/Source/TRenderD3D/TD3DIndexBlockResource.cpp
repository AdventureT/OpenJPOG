#include "TRenderD3D/TD3DIndexBlockResource.h"
#include "TRenderD3D/TD3DIndexPoolResource.h"
#include "TRenderD3D/TD3DIndexFactoryResource.h"
#include "TRenderD3D/TRenderD3DInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TIndexBlockResource, TResource)
IMPLEMENT_FREELIST(TIndexBlockResource, 0, 8)

// $TRenderD3DInterface: FUNCTION 1000ad30
TBOOL TIndexBlockResource::CanFit(TIndexPoolResource *a_pPoolResource)
{
	if (!(GetFlags() & 1) && (GetFlags() & 4)) {
		return a_pPoolResource->GetFlags() & 4;
	}
	if ((GetFlags() & 1) && (a_pPoolResource->GetFlags() & 1)) {
		return m_uiMaxIndices >= a_pPoolResource->GetNumIndices() + m_uiIndicesUsed;
	}
	return TFALSE;
}

// $TRenderD3DInterface: FUNCTION 1000ae90
TBOOL TIndexBlockResource::Lock(TIndexPoolResourceInterface::LockBuffer *a_pLockBuffer, TUSHORT a_usNumVertices)
{
	TVALIDADDRESS(a_pLockBuffer);
	DWORD uiFlags;
	TUINT uiNumIndices = 0;
	TUINT uiUnk1        = m_uiFlags & 7;
	if (uiUnk1 == 1) {
		uiFlags                   = D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->m_uiOffset = 0;
	}
	else if (uiUnk1 == 2) {
		Validate();
		uiFlags                   = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
		a_pLockBuffer->m_uiOffset = 0;
	}
	else if (uiUnk1 == 4) {
		TASSERT(m_uiLockCount == 0);
		Validate();
		uiNumIndices = a_usNumVertices;
		if (m_uiMaxIndices < m_uiOffset + uiNumIndices) {
			uiFlags                   = D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->m_uiOffset = 0;
			m_uiOffset                = uiNumIndices;
		}
		else {
			uiFlags                   = D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK;
			a_pLockBuffer->m_uiOffset = m_uiOffset;
			m_uiOffset += uiNumIndices;
		}
	}
	HRESULT hRes = m_HALBuffer.pIndexBuffer->Lock(a_pLockBuffer->m_uiOffset * 2, uiNumIndices * 2, reinterpret_cast<BYTE **>(&a_pLockBuffer->m_pBuffer), uiFlags);
	TRenderD3DInterface::TD3DAssert(hRes, "Couldn't lock stream index buffer");
	m_uiLockCount++;
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000b020
void TIndexBlockResource::Unlock()
{
	TASSERT(m_uiLockCount > 0);
	HRESULT hRes = m_HALBuffer.pIndexBuffer->Unlock();
	TRenderD3DInterface::TD3DAssert(hRes, "Couldn't unlock stream index buffer");
	m_uiLockCount--;
}

// $TRenderD3DInterface: FUNCTION 1000ada0
TBOOL TIndexBlockResource::GetHAL(TIndexBlockResource::HALBuffer *a_pHALBuffer)
{
	TVALIDADDRESS(a_pHALBuffer);
	if (!Validate()) {
		return TFALSE;
	}
	*a_pHALBuffer = m_HALBuffer;
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000aa90
TBOOL TIndexBlockResource::AttachPool(TIndexPoolResource *a_pPool)
{
	TVALIDADDRESS(a_pPool);
	m_uiIndicesUsed += a_pPool->GetNumIndices();
	a_pPool->SetParent(this);
	if (GetFlags() & 1) {
		Invalidate();
	}
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000ab10
TBOOL TIndexBlockResource::DetachPool(TIndexPoolResource *a_pPool)
{
	TVALIDADDRESS(a_pPool);
	TASSERT(a_pPool->Parent() == this);
	TResource *pIndexFactory = Parent();
	TASSERT(TTRUE == pIndexFactory->GetClass().IsExactly(TGetClass(TIndexFactoryResource)));
	a_pPool->SetParent(pIndexFactory);
	TASSERT(m_uiIndicesUsed >= a_pPool->GetNumIndices());
	m_uiIndicesUsed -= a_pPool->GetNumIndices();
	if (m_uiIndicesUsed == 0 && Child() == TNULL) {
		GetRenderer()->DestroyResource(this);
		return TTRUE;
	}
	TASSERT(Child() != TNULL);
	return TFALSE;
}

struct CallbackStruct
{
	TIndexBlockResource                    *m_pIndexBlock;    // 0x0
	TIndexPoolResourceInterface::LockBuffer m_oHALStaticLock; // 0x4
};

// $TRenderD3DInterface: FUNCTION 1000a670
static TBOOL CallBack(TResource *a_pResource, TPVOID a_pUserData)
{
	CallbackStruct     *pData = TSTATICCAST(CallbackStruct *, a_pUserData);
	TIndexPoolResource *pPool = TSTATICCAST(TIndexPoolResource *, a_pResource);
	if (!a_pResource->IsExactly(TGetClass(TIndexPoolResource))) {
		return TTRUE;
	}
	if (!(pPool->GetFlags() & 1)) {
		return TTRUE;
	}
	TIndexFactoryResource *pFactory = TSTATICCAST(TIndexFactoryResource *, pPool->GetFactory());
	pPool->m_uiIndexOffset          = pData->m_oHALStaticLock.m_uiStartIndex;
	pData->m_oHALStaticLock.m_uiStartIndex += pPool->GetNumIndices();
	TASSERT(pData->m_oHALStaticLock.m_uiStartIndex <= pData->m_pIndexBlock->GetMaxIndices());
	TSystem::MemCopy(
		pData->m_oHALStaticLock.m_pBuffer + pPool->m_uiIndexOffset * 2,
		pPool->GetManagedBuffer(),
		pPool->GetNumIndices() * 2);
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000a910
TBOOL TIndexBlockResource::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}
	TASSERT(TTRUE == Parent()->GetClass().IsExactly(TGetClass(TIndexFactoryResource)));
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

// $TRenderD3DInterface: FUNCTION 1000a870
TBOOL TIndexBlockResource::Create(TIndexFactoryResource *a_pFactory, TUSHORT a_uiMaxIndices, TUINT a_uiFlags)
{
	TASSERT(TFALSE==IsCreated());
	TVALIDADDRESS(a_pFactory);
	m_pFactory      = a_pFactory;
	m_uiMaxIndices = a_uiMaxIndices;
	m_uiFlags       = a_uiFlags;
	return TResource::Create();
}

// $TRenderD3DInterface: FUNCTION 1000b0b0
TBOOL TIndexBlockResource::CreateHAL()
{
	DestroyHAL();
	TRenderD3DInterface  *pRenderer    = static_cast<TRenderD3DInterface *>(GetRenderer());
	DWORD                usage     = D3DUSAGE_WRITEONLY;
	if (GetFlags() & 1) {
		usage      = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
		m_uiOffset = 0;
	}
	if (!pRenderer->GetCurrentDevice()->SupportsHardwareTransfomations()) {
		usage |= D3DUSAGE_SOFTWAREPROCESSING;
	}
	HRESULT hRes = pRenderer->GetD3DDevice()->CreateIndexBuffer(
		GetMaxIndices() * 2,
		usage,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_HALBuffer.pIndexBuffer);
	TRenderD3DInterface::TD3DAssert(hRes, "Unable to create a new index buffer!");
	if (SUCCEEDED(hRes)) {
		TMemory::HALMemInfo memInfoHAL;
		TMemory::GetHALMemInfo(memInfoHAL);
		s_iHALMemoryUsage += memInfoHAL.m_iMemUsage;
		return TTRUE;
	}
	return TFALSE;
}

// $TRenderD3DInterface: FUNCTION 1000b170
void TIndexBlockResource::DestroyHAL()
{
	TMemory::HALMemInfo memInfoHAL;
	TMemory::GetHALMemInfo(memInfoHAL);
	if (m_HALBuffer.pIndexBuffer) {
		TD3DRELEASE(m_HALBuffer.pIndexBuffer);
		m_HALBuffer.pIndexBuffer = TNULL;
	}
	TMemory::GetHALMemInfo(memInfoHAL);
	s_iHALMemoryUsage -= memInfoHAL.m_iMemUsage;
}
