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

		TUINT uiNumStreams;
		TUINT32 uiOffset;
		unsigned char* apStreams[TVertexFactoryFormat::MAX_NUM_STREAMS];
	};

	TVertexPoolResourceInterface();

protected:
	virtual void OnDestroy() override;
	virtual TBOOL Lock(LockBuffer* a_pLockBuffer) = 0;
	virtual void Unlock(TUSHORT a_uiNewNumVertices) = 0;
	virtual TBOOL Create(TVertexFactoryResourceInterface* a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags);
	
public:

	TVertexFactoryResourceInterface* GetFactory() { return m_pFactory; }
	TUINT GetFlags() const { return m_usFlags; }
	TUINT GetMaxVertices() const { return m_usMaxVertices; }
	TUINT GetNumVertices() const { return m_usNumVertices; }
	TBOOL IsLocked() const { return m_uiLockCount != 0; }

private:
	                                             // TResource base 0x0 -> 0x30
	TVertexFactoryResourceInterface* m_pFactory; // 0x30
	TUSHORT m_usFlags;                           // 0x34
	TUSHORT m_usMaxVertices;                     // 0x36
	TUSHORT m_usNumVertices;                     // 0x38
	TUINT m_uiLockCount;                         // 0x3A
};

TOSHI_NAMESPACE_END