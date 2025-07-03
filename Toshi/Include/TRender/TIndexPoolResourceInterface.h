#pragma once
#include "TIndexFactoryResourceInterface.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TIndexPoolResourceInterface : public TResource
{
	DECLARE_DYNAMIC(TIndexPoolResourceInterface)

public:

	TIndexPoolResourceInterface();

protected:
	virtual void  OnDestroy() override;
	virtual TBOOL Lock(void *a_pLockBuffer)    = 0;
	virtual void  Unlock(TUSHORT a_uiNewNumVertices) = 0;
	virtual TBOOL Create(TIndexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags);

public:
	// $TRenderInterface: FUNCTION 1000fd00
	TIndexFactoryResourceInterface *GetFactory() { return m_pFactory; }
	// $TRenderInterface: FUNCTION 1000fcb0
	TUINT GetFlags() const { return m_usFlags; }
	// $TRenderInterface: FUNCTION 1000fcc0
	TUINT GetMaxIndices() const { return m_usMaxIndices; }
	// $TRenderInterface: FUNCTION 1000fcd0
	TUINT GetNumIndices() const { return m_usNumIndices; }
	// $TRenderInterface: FUNCTION 1000fce0
	TBOOL IsLocked() const { return m_uiLockCount != 0; }

private:
	// TResource base 0x0 -> 0x30
	TIndexFactoryResourceInterface  *m_pFactory;      // 0x30
	TUSHORT                          m_usFlags;       // 0x34
	TUSHORT                          m_usMaxIndices;  // 0x36
	TUSHORT                          m_usNumIndices;  // 0x38
	TUINT                            m_uiLockCount;   // 0x3A
};

TOSHI_NAMESPACE_END
