#pragma once
#include "TResource.h"

TOSHI_NAMESPACE_BEGIN

class TIndexPoolResourceInterface;

class TRENDERINTERFACE_EXPORTS TIndexFactoryResourceInterface : public TResource
{
	DECLARE_DYNAMIC(TIndexFactoryResourceInterface)

	friend TIndexPoolResourceInterface;

public:
	TIndexFactoryResourceInterface();

	virtual TBOOL                         Create(TUSHORT a_uiMaxStaticIndices, TUINT a_uiFlags);
	virtual TIndexPoolResourceInterface  *CreatePool(TUSHORT a_uiMaxStaticIndices, TUINT a_uiFlags);

	// $TRenderInterface: FUNCTION 1000fa60
	TUSHORT GetMaxStaticIndices() { return m_usMaxStaticIndices; }
	// $TRenderInterface: FUNCTION 1000fa50
	TUINT GetFlags() { return m_uiFlags; }

private:
	TUINT m_uiNumCreatedIndexPools;  // 0x30
	TUINT m_usMaxStaticIndices;      // 0x34
	TUINT m_uiFlags;                 // 0x38
};

TOSHI_NAMESPACE_END
