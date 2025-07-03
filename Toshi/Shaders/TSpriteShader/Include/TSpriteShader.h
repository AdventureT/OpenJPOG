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
	enum FLAGS
	{
		FLAGS_LOCKED = 0x8000
	};

public:
	TSpriteMesh()
	{
		m_uiFlags     = 0;
		m_pVertexPool = TNULL;
		m_pIndexPool  = TNULL;
	}

	virtual TBOOL Validate();
	virtual void  Unlock(TUSHORT a_iX, TUSHORT a_iY);
	virtual TBOOL Lock();

private:
	TSpriteShader                *m_pShader;     // 0x34
	TUINT                         m_uiFlags;     // 0x38
	TVertexPoolResourceInterface *m_pVertexPool; // 0x40
	TIndexPoolResourceInterface  *m_pIndexPool;  // 0x44
};

class TSpriteMaterial : public TMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterial)

public:
	TSpriteMaterial()
	{
		m_pTexture[0] = TNULL;
		m_pTexture[1] = TNULL;
		m_eBlendMode  = 0;
	}

	virtual void SetBlendMode(TINT a_eBlendMode)
	{
		m_eBlendMode = a_eBlendMode;
	}

	void SetTexture1(TTextureResource *a_pTexture)
	{
		m_pTexture[0] = a_pTexture;
	}

	void SetTexture2(TTextureResource *a_pTexture)
	{
		m_pTexture[1] = a_pTexture;
	}

protected:
	TTextureResource *m_pTexture[2]; // 0x40
	TINT              m_eBlendMode;  // 0x48
};

class TSpriteShader : public TShader
{
	DECLARE_DYNAMIC(TSpriteShader)
public:
	TSpriteShader()
	{
	}

	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName) = 0;
	virtual void             SetMaterial(TSpriteMaterial *a_pMaterial);
	virtual void             SetColour(const TGUIColour &a_rColour);
	virtual void             BeginMeshGeneration();
	virtual void             EndMeshGeneration();

public:
	TSpriteMesh *GetMesh()
	{
		return m_aMeshes.Tail()->Get();
	}

private:
	TNodeList<TNodeListNodeWrapper<TSpriteMesh>> m_aMeshes; // 0xDC
	TUSHORT                                      m_iWidth;  // 0x110
	TUSHORT                                      m_iHeight; // 0x114
};

TOSHI_NAMESPACE_END