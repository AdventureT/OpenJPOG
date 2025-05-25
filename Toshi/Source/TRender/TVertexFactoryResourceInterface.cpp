#include "TVertexFactoryResourceInterface.h"
#include "TVertexPoolResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TVertexFactoryResourceInterface, TResource)

// $TRenderInterface: FUNCTION 10012590
TVertexFactoryResourceInterface::TVertexFactoryResourceInterface()
{
	m_uiNumCreatedVertexPools = 0;
	m_usMaxStaticVertices     = 0;
	m_uiFlags                 = 0;
}

// $TRenderInterface: FUNCTION 10012620
TBOOL TVertexFactoryResourceInterface::Create(TVertexFactoryFormat *a_pVertexFormat, TUSHORT a_uiMaxStaticVertices, TUINT a_uiFlags)
{
	TVALIDADDRESS(a_pVertexFormat);

	m_oVertexFormat       = *a_pVertexFormat;
	m_usMaxStaticVertices = a_uiMaxStaticVertices;
	m_uiFlags             = a_uiFlags;
	return TResource::Create();
}

// $TRenderInterface: FUNCTION 100126f0
TVertexPoolResourceInterface *TVertexFactoryResourceInterface::CreatePool(TUSHORT a_usMaxStaticVertices, TUINT a_uiFlags)
{
	m_uiNumCreatedVertexPools++;
	return TNULL;
}
