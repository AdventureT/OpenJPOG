#include "TIndexPoolResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TIndexPoolResourceInterface, TResource)

// $TRenderInterface: FUNCTION 1000fba0
TIndexPoolResourceInterface::TIndexPoolResourceInterface()
{
	m_pFactory     = TNULL;
	m_usFlags      = 0;
	m_usMaxIndices = 0;
	m_usNumIndices = 0;
	m_uiLockCount  = 0;
}

TBOOL TIndexPoolResourceInterface::Lock(TIndexPoolResourceInterface::LockBuffer *a_pLockBuffer)
{
	return TTRUE;
}

void TIndexPoolResourceInterface::Unlock(TUSHORT a_uiNewNumVertices)
{
}

// $TRenderInterface: FUNCTION 1000fbd0
void TIndexPoolResourceInterface::OnDestroy()
{
	TASSERT(0 == m_uiLockCount);
	m_pFactory->m_uiNumCreatedIndexPools--;
	TResource::OnDestroy();
}

// $TRenderInterface: FUNCTION 1000fc80
TBOOL TIndexPoolResourceInterface::Create(TIndexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxIndices, TUINT a_uiFlags)
{
	m_pFactory     = a_pFactory;
	m_usMaxIndices = a_uiMaxIndices;
	m_usFlags      = a_uiFlags;
	return TResource::Create();
}
