#pragma once
#include "D3D/Defines.h"
#include "Toshi/Toshi.h"
#include "TRender/TShader.h"
#include "TGUI/TGUIColour.h"
#include "TRender/TTextureResource.h"
#include "TRender/TModel.h"
#include "TRender/TIndexPoolResourceInterface.h"
#include "TRender/TVertexPoolResourceInterface.h"

TOSHI_NAMESPACE_BEGIN

class TSpriteShader;

class TSpriteMesh : public TMesh
{
	DECLARE_DYNAMIC(TSpriteMaterial)

	friend class TSpriteShader;

	enum FLAGS
	{
		FLAGS_LOCKED = 0x8000
	};

public:
	TSpriteMesh()
	{
		m_uiFlags     = 0;
		m_bRender     = 0;
		m_pVertexPool = TNULL;
		m_pIndexPool  = TNULL;
	}

	virtual TBOOL Create(TUINT a_uiFlags, TUSHORT a_iX, TUSHORT a_iY) = 0;
	virtual TBOOL Validate();
	virtual void  Unlock(TUSHORT a_iX, TUSHORT a_iY);
	virtual TBOOL Lock();

	// $TSpriteShaderD3D: FUNCTION 10001f20
	void SetVertexPool(TVertexPoolResourceInterface *a_pVertexPool)
	{
		m_pVertexPool = a_pVertexPool;
	}

	// $TSpriteShaderD3D: FUNCTION 10001f10
	void SetIndexPool(TIndexPoolResourceInterface *a_pIndexPool)
	{
		m_pIndexPool = a_pIndexPool;
	}

protected:
	TUINT                         m_uiFlags;     // 0x38
	TBOOL                         m_bRender;     // 0x3E
	TVertexPoolResourceInterface *m_pVertexPool; // 0x40
	TIndexPoolResourceInterface  *m_pIndexPool;  // 0x44
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

protected:
	TTextureResource *m_pTexture;    // 0x40
	TINT              m_eBlendMode;  // 0x44
	TINT              m_eBlendMode2; // 0x48
};

class TSpriteShader : public TShader
{
	DECLARE_DYNAMIC(TSpriteShader)

public:

	TSpriteShader()
	{
		m_pVertexLockBuffer = TNULL;
		m_iNumIndices       = 0;
		m_iNumVertices      = 0;
		m_uiFlags           = 100;
		m_usMaxStaticIndices               = 6144;
		m_usMaxStaticVertices               = 9216;
	}

	virtual TBOOL            Create();
	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName) = 0;
	virtual TSpriteMesh     *CreateMesh(TINT a_iCount, TINT &a_rMeshSize) = 0;
	virtual void             SetMaterial(TSpriteMaterial *a_pMaterial);
	virtual void             SetColour(const TGUIColour &a_rColour);
	virtual void             BeginMeshGeneration();
	virtual void             EndMeshGeneration();

public:

	TSpriteMesh *GetMesh()
	{
		return m_aMeshes.Tail()->Get();
	}

protected:
	TVertexPoolResourceInterface::LockBuffer    *m_pVertexLockBuffer;   // 0xE0
	TNodeList<TNodeListNodeWrapper<TSpriteMesh>> m_aMeshes;             // 0xDC
	TUSHORT                                      m_iNumIndices;         // 0x110
	TUSHORT                                      m_iNumVertices;        // 0x114
	TUINT                                        m_uiFlags;             // 0x120
	TUSHORT                                      m_usMaxStaticVertices; // 0x124
	TUSHORT                                      m_usMaxStaticIndices;  // 0x126
};

TOSHI_NAMESPACE_END