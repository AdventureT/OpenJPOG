#pragma once
#include "TRender/TResource.h"
#include "TKernel/TFreeList.h"
#include "TKernel/TSystemTools.h"
#include "TRender/TVertexFactoryResourceInterface.h"
#include "TRender/TVertexPoolResourceInterface.h"
#include <d3d8.h>
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TVertexPoolResource;
class TVertexFactoryResource;

class TRENDERINTERFACED3D_EXPORTS TVertexBlockResource : public TResource
{
	DECLARE_DYNAMIC(TVertexBlockResource)
	DECLARE_FREELIST(TVertexBlockResource)

public:
	struct TRENDERINTERFACED3D_EXPORTS HALBuffer
	{
		HALBuffer()
		{
			uiNumStreams = 0;
			uiVertexOffset = 0;
			TSystem::MemSet(apVertexBuffers, 0, sizeof(apVertexBuffers));
		}

		TUINT                   uiNumStreams;
		TUSHORT                 uiVertexOffset;
		IDirect3DVertexBuffer8 *apVertexBuffers[TVertexFactoryFormat::MAX_NUM_STREAMS];
	};

	TVertexBlockResource()
	{
		m_pFactory       = TNULL;
		m_uiFlags        = 0;
		m_uiMaxVertices  = 0;
		m_uiOffset       = 0;
		m_uiVerticesUsed = 0;
		m_uiLockCount    = 0;
		m_Unk1           = 0;
	}

	virtual TBOOL Validate();

	TBOOL Create(TVertexFactoryResource *a_pFactory, TUSHORT a_uiMaxVertices, TUINT a_uiFlags);

protected:

	TBOOL CreateHAL();
	void  DestroyHAL();

public:

	TBOOL AttachPool(TVertexPoolResource *a_pPool);
	TBOOL DetachPool(TVertexPoolResource *a_pPool);
	TBOOL CanFit(TVertexPoolResource *a_pPoolResource);

	TBOOL Lock(TVertexPoolResourceInterface::LockBuffer *a_pLockBuffer, TUSHORT a_usNumVertices);
	void Unlock();

	// $TRenderD3DInterface: FUNCTION 10008e90
	void ChildVertexUsedChanged(TINT a_iChange)
	{
		if (a_iChange < 0) {
			TASSERT(m_uiVerticesUsed >= -a_iChange);
		}
		m_uiVerticesUsed += a_iChange;
	}

	// $TRenderD3DInterface: FUNCTION 10009510
	TVertexFactoryResourceInterface *GetFactory()
	{
		return m_pFactory;
	}
	// $TRenderD3DInterface: FUNCTION 100094e0
	TUINT GetFlags() 
	{
		return m_uiFlags;
	}
	// $TRenderD3DInterface: FUNCTION 10009500
	TUSHORT GetMaxVertices()
	{
		return m_uiMaxVertices;
	}

	inline static TINT s_iCurrentNumHALCreated;
	inline static TINT s_iTotalNumHALCreated;
	inline static TINT s_iTotalNumHALDestroyed;
	inline static TINT s_iCurrentVertexBufferBytesAllocated;
	inline static TINT s_iTotalVertexBufferBytesAllocated;
	inline static TINT s_iHALMemoryUsage;
	inline static TINT s_iWastedVertexBufferBytesAllocated;

private:
	TVertexFactoryResourceInterface *m_pFactory; // 0x30
	TUINT                            m_uiFlags;  // 0x34
	TUSHORT                          m_uiMaxVertices;
	TUINT                            m_uiOffset; // 0x3C
	TUINT                            m_uiVerticesUsed;
	TUINT                            m_uiLockCount;
	TUINT                            m_Unk1;
	HALBuffer                        m_HALBuffer;
};

TOSHI_NAMESPACE_END
