#pragma once
#include "TRender/TResource.h"
#include "TKernel/TFreeList.h"
#include "TKernel/TSystemTools.h"
#include "TRender/TIndexFactoryResourceInterface.h"
#include "TRender/TIndexPoolResourceInterface.h"
#include <d3d8.h>
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TIndexPoolResource;
class TIndexFactoryResource;

class TRENDERINTERFACED3D_EXPORTS TIndexBlockResource : public TResource
{
	DECLARE_DYNAMIC(TIndexBlockResource)
	DECLARE_FREELIST(TIndexBlockResource)

public:
	struct TRENDERINTERFACED3D_EXPORTS HALBuffer
	{
		TUINT                  m_uiIndexOffset = 0;
		IDirect3DIndexBuffer8 *pIndexBuffer    = NULL;
	};

	TIndexBlockResource()
	{
		m_pFactory       = TNULL;
		m_uiFlags        = 0;
		m_uiMaxIndices  = 0;
		m_uiOffset       = 0;
		m_uiIndicesUsed = 0;
		m_uiLockCount    = 0;
		m_Unk1           = 0;
	}

	virtual TBOOL Validate();

	TBOOL Create(TIndexFactoryResource *a_pFactory, TUSHORT a_uiMaxVertices, TUINT a_uiFlags);

protected:
	TBOOL CreateHAL();
	void  DestroyHAL();

public:

	TBOOL GetHAL(TIndexBlockResource::HALBuffer *a_pHALBuffer);

	TBOOL AttachPool(TIndexPoolResource *a_pPool);
	TBOOL DetachPool(TIndexPoolResource *a_pPool);
	TBOOL CanFit(TIndexPoolResource *a_pPoolResource);

	TBOOL Lock(TIndexPoolResourceInterface::LockBuffer *a_pLockBuffer, TUSHORT a_usNumVertices);
	void  Unlock();

	// $TRenderD3DInterface: FUNCTION 1000ae20
	void ChildIndexUsedChanged(TINT a_iChange)
	{
		if (a_iChange < 0) {
			TASSERT(m_uiIndicesUsed >= -a_iChange);
		}
		m_uiIndicesUsed += a_iChange;
	}

	// $TRenderD3DInterface: FUNCTION 1000b2f0
	TIndexFactoryResourceInterface *GetFactory()
	{
		return m_pFactory;
	}
	// $TRenderD3DInterface: FUNCTION 1000b2c0
	TUINT GetFlags()
	{
		return m_uiFlags;
	}
	// $TRenderD3DInterface: FUNCTION 1000b2e0
	TUSHORT GetMaxIndices() const
	{
		return m_uiMaxIndices;
	}
	// $TRenderD3DInterface: FUNCTION 1000b2d0
	TUSHORT GetIndicesUsed() const
	{
		return m_uiMaxIndices;
	}

	inline static TINT s_iHALMemoryUsage;

private:
	TIndexFactoryResourceInterface *m_pFactory;      // 0x30
	TUINT                           m_uiFlags;       // 0x34
	TUSHORT                         m_uiMaxIndices;  // 0x38
	TUINT                           m_uiOffset;      // 0x3C
	TUINT                           m_uiIndicesUsed; // 0x40
	TUINT                           m_uiLockCount;   // 0x44
	TUINT                           m_Unk1;
	HALBuffer                       m_HALBuffer;
};

TOSHI_NAMESPACE_END
