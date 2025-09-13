#pragma once
#include "TRenderD3D/TD3DIndexPoolResource.h"
#include "TRenderD3D/TD3DIndexBlockResource.h"
#include "TRender/TIndexFactoryResourceInterface.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TIndexFactoryResource : public TIndexFactoryResourceInterface
{
public:
	DECLARE_DYNAMIC(TIndexFactoryResource);

public:
	virtual TIndexPoolResourceInterface *CreatePoolResource(TUINT16 a_uiMaxStaticIndices, TUINT16 a_uiFlags);

	TIndexBlockResource *FindBlockResource(TIndexPoolResource *a_pResource);
	TIndexBlockResource *CreateBlockResource(TUINT16 a_uiMaxIndices, TUINT32 a_uiFlags);
};

TOSHI_NAMESPACE_END
