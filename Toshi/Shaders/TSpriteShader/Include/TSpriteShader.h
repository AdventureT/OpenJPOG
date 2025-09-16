#pragma once
#include "D3D/Defines.h"
#include "Toshi/Toshi.h"
#include "TRender/TShader.h"
#include "TGUI/TGUIColour.h"
#include "TRender/TTextureResource.h"
#include "TRender/TModel.h"
#include "TRender/TIndexPoolResourceInterface.h"
#include "TRender/TVertexPoolResourceInterface.h"
#include "TKernel/TMatrix44.h"
#include "TKernel/TVector2.h"
#include "TKernel/TVector3.h"

TOSHI_NAMESPACE_BEGIN

class TSpriteShader;

class TSpriteMesh : public TMesh
{
	DECLARE_DYNAMIC(TSpriteMesh)

	friend class TSpriteShader;

	enum FLAGS
	{
		FLAGS_LOCKED = 0x8000
	};

public:
	TSpriteMesh()
		: m_vPos1(1.0f, 1.0f), m_vPos2(1.0f, 1.0f), m_vUV1(0.0f, 0.0f), m_vUV2(0.0f, 0.0f)
	{
		m_uiFlags           = 0;
		m_iDeltaNumVertices = 0;
		m_iDeltaNumIndices  = 0;
		m_pVertexPool       = TNULL;
		m_pIndexPool        = TNULL;
	}

	virtual TBOOL Create(TUINT a_uiFlags, TUSHORT a_iX, TUSHORT a_iY) = 0;
	virtual TBOOL Validate();
	virtual void  Unlock(TUSHORT a_iX, TUSHORT a_iY);
	virtual TBOOL Lock();

	// $TSpriteShaderD3D: FUNCTION 10001f40
	TVertexPoolResourceInterface *GetVertexPool()
	{
		return m_pVertexPool;
	}

	// $TSpriteShaderD3D: FUNCTION 10001f20
	void SetVertexPool(TVertexPoolResourceInterface *a_pVertexPool)
	{
		m_pVertexPool = a_pVertexPool;
	}

	// $TSpriteShaderD3D: FUNCTION 10001f30
	TIndexPoolResourceInterface *GetIndexPool()
	{
		return m_pIndexPool;
	}

	// $TSpriteShaderD3D: FUNCTION 10001f10
	void SetIndexPool(TIndexPoolResourceInterface *a_pIndexPool)
	{
		m_pIndexPool = a_pIndexPool;
	}

	TUSHORT GetNumIndices()
	{
		return m_iNumIndices;
	}

	TUSHORT GetDeltaNumIndices()
	{
		return m_iDeltaNumIndices;
	}

	TUSHORT GetDeltaNumVertices()
	{
		return m_iDeltaNumVertices;
	}

	TUSHORT GetNumVertices()
	{
		return m_iNumVertices;
	}

protected:
	TUINT                         m_uiFlags;           // 0x38
	TUSHORT                       m_iDeltaNumVertices; // 0x3C
	TUSHORT                       m_iDeltaNumIndices;  // 0x3E
	TVertexPoolResourceInterface *m_pVertexPool;       // 0x40
	TIndexPoolResourceInterface  *m_pIndexPool;        // 0x44
	TVector2                      m_vPos1;             // 0x48
	TVector2                      m_vPos2;             // 0x50
	TVector2                      m_vUV1;              // 0x58
	TVector2                      m_vUV2;              // 0x60
	TUSHORT                       m_iNumIndices;       // 0x68
	TUSHORT                       m_iNumVertices;      // 0x6A
};

class TSpriteMaterial : public TMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterial)

public:
	TSpriteMaterial()
	{
		m_pTexture    = TNULL;
		m_eBlendMode  = 0;
		m_eBlendMode2 = 0;
	}

	virtual void SetBlendMode(TINT a_eBlendMode)
	{
		m_eBlendMode = a_eBlendMode;
	}

	virtual void SetBlendMode2(TINT a_eBlendMode)
	{
		m_eBlendMode2 = m_eBlendMode2;
	}

	void SetTexture(TTextureResource *a_pTexture)
	{
		m_pTexture = a_pTexture;
	}

	TINT GetBlendMode()
	{
		return m_eBlendMode;
	}

protected:
	TTextureResource *m_pTexture;    // 0x40
	TINT              m_eBlendMode;  // 0x44
	TINT              m_eBlendMode2; // 0x48
};

class TSpriteShader : public TShader
{
	DECLARE_DYNAMIC(TSpriteShader)

public:
	struct Vertex
	{
		Toshi::TVector3 Position;
		TUINT32         Colour = 0;
		Toshi::TVector2 UV;
	};


	TSpriteShader()
		: m_vPos1(1.0f, 1.0f), m_vPos2(1.0f, 1.0f)
	{
		m_bForceRender        = TFALSE;
		m_pCurrentMesh        = TNULL;
		m_iNumIndices         = 0;
		m_iNumVertices        = 0;
		m_pLineMaterial       = TNULL;
		m_pFillMaterial       = TNULL;
		m_uiFlags             = 100;
		m_usMaxStaticIndices  = 6144;
		m_usMaxStaticVertices = 9216;
		m_unkFlags            = m_unkFlags & 0x80 | 0x4E;
		m_pMaterial           = TNULL;
	}

	virtual TBOOL            Create();
	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName)             = 0;
	virtual TSpriteMesh     *CreateMesh(TINT a_iCount, TINT &a_rMeshSize) = 0;
	virtual TSpriteMesh     *CreateMesh(TPCCHAR a_szName)                 = 0;
	virtual void             SetMaterial(TSpriteMaterial *a_pMaterial);
	virtual void             SetColour(const TGUIColour &a_rColour);
	virtual void             BeginMeshGeneration();
	virtual void             EndMeshGeneration();
	virtual void             RenderTriStrip(TFLOAT pos1x, TFLOAT pos1y, TFLOAT pos2x, TFLOAT pos2y, TFLOAT a_fColour, TFLOAT uv1x, TFLOAT uv1y, TFLOAT uv2x, TFLOAT uv2y);

public:
	TSpriteMesh *FUN_10001ad0(TUSHORT a_iNumVertices, TUSHORT a_iNumIndices);
	void         FUN_100019e0();
	void         FUN_10001b60();

	TSpriteMesh *GetMesh()
	{
		return m_pCurrentMesh->Get();
	}

	TUSHORT GetNumIndices()
	{
		return m_iNumIndices;
	}

	TUSHORT GetNumVertices()
	{
		return m_iNumVertices;
	}

protected:
	TINT                                     m_unkFlags;            // 0x30
	TSpriteMaterial                         *m_pMaterial;           // 0x4C
	TGUIColour                               m_oColour;             // 0x50
	TVector2                                 m_vPos1;               // 0x54
	TVector2                                 m_vPos2;               // 0x5C
	TVector2                                 m_vUV1;                // 0x64
	TVector2                                 m_vUV2;                // 0x6C
	TBOOL                                    m_bForceRender;        // 0xC8
	TNodeList<TNodeWrapper<TSpriteMesh>>     m_aMeshes;             // 0xCC
	TNodeWrapper<TSpriteMesh>               *m_pCurrentMesh;        // 0xDC
	TVertexPoolResourceInterface::LockBuffer m_VertexLockBuffer;    // 0xE0
	Vertex                                   m_aVertices[4];        // 0xE8
	TMatrix44                                m_oModelViewMatrix;    // 0x8C
	TIndexPoolResourceInterface::LockBuffer  m_IndexLockBuffer;     // 0x108
	TUSHORT                                  m_iNumIndices;         // 0x110
	TUSHORT                                  m_iNumVertices;        // 0x114
	TSpriteMaterial                         *m_pLineMaterial;       // 0x118
	TSpriteMaterial                         *m_pFillMaterial;       // 0x11C
	TUINT                                    m_uiFlags;             // 0x120
	TUSHORT                                  m_usMaxStaticVertices; // 0x124
	TUSHORT                                  m_usMaxStaticIndices;  // 0x126
};

TOSHI_NAMESPACE_END