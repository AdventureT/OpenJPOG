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

	TVertexPoolResource()
	{
		m_uiVertexOffset = 0;
		m_uiNumLocksOverall = 0;
		TSystem::MemSet(m_apManagedStreams, 0, sizeof(m_apManagedStreams));
	}

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

	// $TRenderD3DInterface: FUNCTION 1000a1b0
	TBYTE* GetManagedStream(TUINT a_uiStream)
	{
		TASSERT(a_uiStream<GetFactory()->GetVertexFormat()->GetNumStreams());
		TASSERT(TFALSE==IsLocked());
		if (!IsLocked() && a_uiStream < GetFactory()->GetVertexFormat()->GetNumStreams()) {
			return m_apManagedStreams[a_uiStream];
		}
		return TNULL;
	}

	TBOOL GetHAL(TVertexBlockResource::HALBuffer *a_pHALBuffer);

public:
	TUINT  m_uiVertexOffset;                                          // 0x3C
	TBYTE *m_apManagedStreams[TVertexFactoryFormat::MAX_NUM_STREAMS]; // 0x40
	TUINT  m_uiNumLocksOverall;                                       // 0x60
};

TOSHI_NAMESPACE_END
