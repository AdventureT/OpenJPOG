#include "TVertexPoolResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TVertexPoolResourceInterface, TResource)

TVertexPoolResourceInterface::LockBuffer::LockBuffer()
{
	uiNumStreams = 0;
	uiOffset     = 0;
	apStreams[0] = TNULL;
	apStreams[1] = TNULL;
	apStreams[2] = TNULL;
	apStreams[3] = TNULL;
	apStreams[4] = TNULL;
	apStreams[5] = TNULL;
	apStreams[6] = TNULL;
	apStreams[7] = TNULL;
}

// $TRenderInterface: FUNCTION 10012840
TVertexPoolResourceInterface::TVertexPoolResourceInterface()
{
	m_pFactory      = TNULL;
	m_usFlags       = 0;
	m_usMaxVertices = 0;
	m_usNumVertices = 0;
	m_uiLockCount   = 0;
}

// $TRenderInterface: FUNCTION 10012870
void TVertexPoolResourceInterface::OnDestroy()
{
	TASSERT(0 == m_uiLockCount);
	m_pFactory->m_uiNumCreatedVertexPools--;
	TResource::OnDestroy();
}

TBOOL TVertexPoolResourceInterface::Lock(LockBuffer *a_pLockBuffer)
{
	return TTRUE;
}

void TVertexPoolResourceInterface::Unlock(TUSHORT a_uiNewNumVertices)
{
}

// $TRenderInterface: FUNCTION 10012920
TBOOL TVertexPoolResourceInterface::Create(TVertexFactoryResourceInterface *a_pFactory, TUINT a_uiMaxVertices, TUINT a_uiFlags)
{
	m_pFactory      = a_pFactory;
	m_usMaxVertices = a_uiMaxVertices;
	m_usFlags       = a_uiFlags;
	return TResource::Create();
}
