#include "TIndexFactoryResourceInterface.h"
#include "TIndexPoolResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TIndexFactoryResourceInterface, TResource)

// $TRenderInterface: FUNCTION 1000fa70
TIndexFactoryResourceInterface::TIndexFactoryResourceInterface()
{
	m_uiNumCreatedIndexPools = 0;
	m_usMaxStaticIndices     = 0;
	m_uiFlags                = 0;
}

// $TRenderInterface: FUNCTION 1000fa30
TBOOL TIndexFactoryResourceInterface::Create(TUSHORT a_uiMaxStaticIndices, TUINT a_uiFlags)
{
	m_usMaxStaticIndices = a_uiMaxStaticIndices;
	m_uiFlags            = a_uiFlags;
	return TResource::Create();
}

// $TRenderInterface: FUNCTION 100126f0
TIndexPoolResourceInterface *TIndexFactoryResourceInterface::CreatePool(TUSHORT a_usMaxStaticIndices, TUINT a_uiFlags)
{
	m_uiNumCreatedIndexPools++;
	return TNULL;
}
