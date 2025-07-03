#pragma once
#include "TVertexFactoryResourceInterface.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TVertexPoolResourceInterface : public TResource
{
	DECLARE_DYNAMIC(TVertexPoolResourceInterface)

public:
	class TRENDERINTERFACE_EXPORTS LockBuffer
	{
		LockBuffer();

		TUINT          uiNumStreams;
		TUINT32        uiOffset;
		unsigned char *apStreams[TVertexFactoryFormat::MAX_NUM_STREAMS];
	};

	TVertexPoolResourceInterface();

protected:
	virtual void  OnDestroy() override;
	virtual TBOOL Lock(LockBuffer *a_pLockBuffer)    = 0;
	virtual void  Unlock(TUSHORT a_uiNewNumVertices) = 0;
	virtual TBOOL Create(TVertexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags);

public:
	// $TRenderInterface: FUNCTION 100129a0
	TVertexFactoryResourceInterface *GetFactory() { return m_pFactory; }
	// $TRenderInterface: FUNCTION 10012950
	TUINT                            GetFlags() const { return m_usFlags; }
	// $TRenderInterface: FUNCTION 10012960
	TUINT                            GetMaxVertices() const { return m_usMaxVertices; }
	// $TRenderInterface: FUNCTION 10012970
	TUINT                            GetNumVertices() const { return m_usNumVertices; }
	// $TRenderInterface: FUNCTION 10012980
	TBOOL                            IsLocked() const { return m_uiLockCount != 0; }

protected:
	// TResource base 0x0 -> 0x30
	TVertexFactoryResourceInterface *m_pFactory;      // 0x30
	TUSHORT                          m_usFlags;       // 0x34
	TUSHORT                          m_usMaxVertices; // 0x36
	TUSHORT                          m_usNumVertices; // 0x38
	TUINT                            m_uiLockCount;   // 0x3A
};

TOSHI_NAMESPACE_END
