#pragma once

#include "TRender/TVertexPoolResourceInterface.h"
#include "TRenderD3D/TD3DVertexBlockResource.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TVertexPoolResource : public TVertexPoolResourceInterface
{
	DECLARE_DYNAMIC(TVertexPoolResource)

	friend class TVertexFactoryResource;

public:

	virtual TBOOL Validate() override;
	virtual void  Invalidate() override;
	virtual void  OnDestroy() override;
	virtual TBOOL Lock(LockBuffer *a_pLockBuffer) override;
	virtual void  Unlock(TUSHORT a_uiNewNumVertices) override;
	virtual TBOOL Create(TVertexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags) override;

public:

	// This function is always inlined 
	TFORCEINLINE TResource *GetParent()
	{
		if (GetTree()) {
			return Parent() == GetTree()->GetRoot() ? TNULL : Parent();
		}
		return Parent();
	}

	TVertexBlockResource *GetVertexBlock()
	{
		if (Parent()->IsExactly(TGetClass(TVertexBlockResource))) {
			return static_cast<TVertexBlockResource *>(Parent());
		}
		return TNULL;
	}
};

TOSHI_NAMESPACE_END
