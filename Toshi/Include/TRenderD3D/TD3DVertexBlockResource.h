#pragma once
#include "TRender/TResource.h"
#include "TKernel/TFreeList.h"
#include "TRender/TVertexFactoryResourceInterface.h"
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
		}

		TUINT                   uiNumStreams;
		TUSHORT                 uiVertexOffset;
		IDirect3DVertexBuffer8 *apVertexBuffers[TVertexFactoryFormat::MAX_NUM_STREAMS];
	};

	TBOOL Create(TVertexFactoryResource *a_pFactory, TUSHORT a_uiMaxVertices, TUINT a_uiFlags);

	TBOOL AttachPool(TVertexPoolResource *a_pPool);
	TBOOL CanFit(TVertexPoolResource *a_pPoolResource);

	TVertexFactoryResourceInterface *GetFactory() { return m_pFactory; }
	TUINT                            GetFlags() { return m_uiFlags; }

private:
	TVertexFactoryResourceInterface *m_pFactory; // 0x30
	TUINT                            m_uiFlags;  // 0x34
	TUSHORT                          m_uiMaxVertices;
	TUINT                            m_uiOffset;
	TUINT                            m_uiVerticesUsed;
	TUINT                            m_uiLockCount;
	TUINT                            m_Unk1;
	HALBuffer                        m_HALBuffer;
};

TOSHI_NAMESPACE_END
