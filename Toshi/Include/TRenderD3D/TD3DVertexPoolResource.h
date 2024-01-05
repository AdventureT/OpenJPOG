#pragma once

#include "TRender/TVertexPoolResourceInterface.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TVertexPoolResource : public TVertexPoolResourceInterface
{
	DECLARE_DYNAMIC(TVertexPoolResource)

	friend class TVertexFactoryResource;

protected:
	virtual TBOOL Validate() override;
	virtual void Invalidate() override;
	virtual void OnDestroy() override;
	virtual TBOOL Lock(LockBuffer* a_pLockBuffer) override;
	virtual void Unlock(TUSHORT a_uiNewNumVertices) override;
	virtual TBOOL Create(TVertexFactoryResourceInterface* a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags) override;
};

TOSHI_NAMESPACE_END