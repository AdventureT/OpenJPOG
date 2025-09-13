#pragma once

#include "TRender/TIndexPoolResourceInterface.h"
#include "TRenderD3D/TD3DIndexBlockResource.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TIndexPoolResource : public TIndexPoolResourceInterface
{
	DECLARE_DYNAMIC(TIndexPoolResource)

	friend class TIndexFactoryResource;

public:
	TIndexPoolResource()
	{
		m_uiIndexOffset     = 0;
		m_uiNumLocksOverall = 0;
		m_apManagedBuffer   = TNULL;
	}

	virtual TBOOL Validate() override;
	virtual void  Invalidate() override;
	virtual void  OnDestroy() override;
	virtual TBOOL Lock(LockBuffer *a_pLockBuffer) override;
	virtual void  Unlock(TUSHORT a_uiNewNumVertices) override;
	virtual TBOOL Create(TIndexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags) override;

public:

	TBOOL GetHAL(TIndexBlockResource::HALBuffer *a_pHALBuffer);

	// This function is always inlined
	TFORCEINLINE TResource *GetParent()
	{
		if (GetTree()) {
			return Parent() == GetTree()->GetRoot() ? TNULL : Parent();
		}
		return Parent();
	}

	// $TRenderD3DInterface: FUNCTION 1000c0a0
	TIndexBlockResource *GetIndexBlock()
	{
		if (Parent()->IsExactly(TGetClass(TIndexBlockResource))) {
			return static_cast<TIndexBlockResource *>(Parent());
		}
		return TNULL;
	}

	// $TRenderD3DInterface: FUNCTION 1000bf70
	unsigned short *GetManagedBuffer()
	{
		TASSERT(TFALSE==IsLocked());
		if (!IsLocked()) {
			return m_apManagedBuffer;
		}
		return TNULL;
	}

public:
	TUINT           m_uiIndexOffset;     // 0x3C
	unsigned short *m_apManagedBuffer;   // 0x40
	TUINT           m_uiNumLocksOverall; // 0x60
};

TOSHI_NAMESPACE_END
