#include "TRenderD3D/TD3DIndexPoolResource.h"
#include "TRenderD3D/TD3DIndexFactoryResource.h"
#include <TRenderD3D/TRenderD3DInterface.h>

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TIndexPoolResource, TResource)

TBOOL TIndexPoolResource::Validate()
{
	if (IsValid()) {
		return TTRUE;
	}
	TIndexFactoryResource *pFactory     = TSTATICCAST(TIndexFactoryResource *, GetFactory());
	TIndexBlockResource   *pIndexBlock = pFactory->FindBlockResource(this);
	if (!pIndexBlock) {
		TUINT32 uiFlags;
		TUSHORT uiNumIndices;

		TUINT8 uiUnk1 = GetFlags() & 7;

		if (uiUnk1 == 1) {
			uiNumIndices = pFactory->GetMaxStaticIndices();
			TASSERT(GetNumIndices() <= uiNumIndices);
			uiFlags = 1;
		}
		else if (uiUnk1 == 2) {
			uiNumIndices = GetMaxIndices();
			uiFlags    = 2;
		}
		else {
			if (uiUnk1 != 4) {
				return TFALSE;
			}
			uiNumIndices = GetMaxIndices();
			uiFlags    = 4;
		}
		pIndexBlock = pFactory->CreateBlockResource(uiNumIndices, uiFlags);
		TVALIDADDRESS(pIndexBlock);
		if (!pIndexBlock) {
			return TFALSE;
		}
	}
	pIndexBlock->AttachPool(this);
	return TIndexPoolResourceInterface::Validate();
}

// $TRenderD3DInterface: FUNCTION 1000bab0
void TIndexPoolResource::Invalidate()
{
	if (!IsValid()) {
		return;
	}
	TASSERT(m_uiLockCount == 0);
	TIndexBlockResource *pIndexBlock = GetIndexBlock();
	TVALIDADDRESS(pIndexBlock);
	pIndexBlock->DetachPool(this);
	TIndexPoolResourceInterface::Invalidate();
}

// $TRenderD3DInterface: FUNCTION 1000c210
void TIndexPoolResource::OnDestroy()
{
	if ((GetFlags() & 1) && m_apManagedBuffer) {
		delete m_apManagedBuffer;
		m_apManagedBuffer = TNULL;
	}
	TIndexPoolResourceInterface::OnDestroy();
}

// $TRenderD3DInterface: FUNCTION 1000bb50
TBOOL TIndexPoolResource::Lock(LockBuffer *a_pLockBuffer)
{
	TVALIDADDRESS(a_pLockBuffer);
	if ((m_uiLockCount++) == 0) {
		TUINT flags = GetFlags() & 7;
		if (flags == 1) {
			TASSERT(TFALSE==IsValid());
			a_pLockBuffer->m_pBuffer = m_apManagedBuffer;
			return TTRUE;
		}
		else if (flags == 2) {
			Validate();
			TIndexBlockResource *pIndexBlock = GetIndexBlock();
			TVALIDADDRESS(pIndexBlock);
			if (pIndexBlock->Lock(a_pLockBuffer, 0)) {
				m_uiIndexOffset = a_pLockBuffer->m_uiOffset;
				return TTRUE;
			}
		}
		else if (flags == 4) {
			Validate();
			TIndexBlockResource *pIndexBlock = GetIndexBlock();
			TVALIDADDRESS(pIndexBlock);
			if (pIndexBlock->Lock(a_pLockBuffer, GetMaxIndices())) {
				m_uiIndexOffset = a_pLockBuffer->m_uiOffset;
				return TTRUE;
			}
		}
	}
	return TFALSE;
}

// $TRenderD3DInterface: FUNCTION 1000bd20
void TIndexPoolResource::Unlock(TUSHORT a_uiNewNumIndices)
{
	TASSERT(m_uiLockCount > 0);
	if (m_uiLockCount > 0 && --m_uiLockCount == 0) {
		TINT iChange = a_uiNewNumIndices - GetNumIndices();
		if (iChange != 0) {
			if (GetParent()) {
				if (GetParent()->GetClass().IsA(TGetClass(TIndexBlockResource))) {
					TIndexBlockResource *pIndexBlock = static_cast<TIndexBlockResource *>(Parent());
					pIndexBlock->ChildIndexUsedChanged(iChange);
				}
			}
		}
		m_usNumIndices = a_uiNewNumIndices;
		if (!(GetFlags() & 6)) {
			if (GetFlags() & 1) {
				Validate();
			}
		}
		else {
			GetIndexBlock()->Unlock();
		}
	}
}

// $TRenderD3DInterface: FUNCTION 1000a3c0
TBOOL TIndexPoolResource::Create(TIndexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxIndices, TUINT a_uiFlags)
{
	TASSERT(TFALSE==IsCreated());
	if (a_uiFlags & 4) {
		a_uiFlags = a_uiFlags & ~4 | 2;
	}
	if (!TIndexPoolResourceInterface::Create(a_pFactory, a_uiMaxIndices, a_uiFlags)) {
		return TFALSE;
	}
	if (GetFlags() & 1) {
		m_apManagedBuffer = new unsigned short[a_uiMaxIndices];
		TVALIDADDRESS(m_apManagedBuffer);
	}
	return TTRUE;
}

// $TRenderD3DInterface: FUNCTION 1000bfd0
TBOOL TIndexPoolResource::GetHAL(TIndexBlockResource::HALBuffer *a_pHALBuffer)
{
	TVALIDADDRESS(a_pHALBuffer);
	if (!Validate()) {
		return TFALSE;
	}
	TIndexBlockResource *pIndexBlock = GetIndexBlock();
	TVALIDADDRESS(pIndexBlock);
	if (!pIndexBlock->GetHAL(a_pHALBuffer)) {
		return TFALSE;
	}
	a_pHALBuffer->m_uiIndexOffset = m_uiIndexOffset;
	return TTRUE;
}
