#pragma once

#include "TRender/TVertexFactoryResourceInterface.h"
#include "TRenderD3D/TD3DVertexPoolResource.h"
#include "TRenderD3D/TD3DVertexBlockResource.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TVertexFactoryResource : public TVertexFactoryResourceInterface
{
	DECLARE_DYNAMIC(TVertexFactoryResource)

public:
	virtual TVertexPoolResourceInterface* CreatePoolResource(TUSHORT a_uiMaxStaticVertices, TUINT a_uiFlags);

	TVertexBlockResource* FindBlockResource(TVertexPoolResource* a_pResource);
	TVertexBlockResource* CreateBlockResource(TUSHORT a_uiMaxVertices, TUINT a_uiFlags);
};

TOSHI_NAMESPACE_END