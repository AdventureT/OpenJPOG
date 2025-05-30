#pragma once
#include "TResource.h"

TOSHI_NAMESPACE_BEGIN

struct TRENDERINTERFACE_EXPORTS TVertexStreamFormat
{
	TUSHORT m_uiUnk        = 0;
	TUSHORT m_uiVertexSize = 0;
	TUINT   m_Unk          = 0;
};

class TRENDERINTERFACE_EXPORTS TVertexFactoryFormat
{
public:
	static constexpr TUINT MAX_NUM_STREAMS = 8;

	TUINT               m_uiNumStreams = 0;
	TVertexStreamFormat m_aStreamFormats[MAX_NUM_STREAMS];

	TUINT GetNumStreams() const { return m_uiNumStreams; }
};

class TVertexPoolResourceInterface;

class TRENDERINTERFACE_EXPORTS TVertexFactoryResourceInterface : public TResource
{
	DECLARE_DYNAMIC(TVertexFactoryResourceInterface)

	friend TVertexPoolResourceInterface;

public:
	TVertexFactoryResourceInterface();

	virtual TBOOL                         Create(TVertexFactoryFormat *a_pVertexFormat, TUSHORT a_uiMaxStaticVertices, TUINT a_uiFlags);
	virtual TVertexPoolResourceInterface *CreatePool(TUSHORT a_usMaxStaticVertices, TUINT a_uiFlags);

	// $TRenderInterface: FUNCTION 10012720
	TVertexFactoryFormat *GetVertexFormat() { return &m_oVertexFormat; }
	// $TRenderInterface: FUNCTION 10012710
	TUSHORT               GetMaxStaticVertices() { return m_usMaxStaticVertices; }
	// $TRenderInterface: FUNCTION 10012700
	TUINT                 GetFlags() { return m_uiFlags; }

private:
	TUINT                m_uiNumCreatedVertexPools; // 0x30
	TVertexFactoryFormat m_oVertexFormat;           // 0x34
	TUINT                m_usMaxStaticVertices;     // 0x78
	TUINT                m_uiFlags;                 // 0x7C
};

TOSHI_NAMESPACE_END
