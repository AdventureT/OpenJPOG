#pragma once
#include "Defines.h"
#include "../TSpriteShader.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"
#include "TRenderD3D/TOrderTable.h"
#include "TRenderD3D/TD3DVertexPoolResource.h"

TOSHI_NAMESPACE_BEGIN

#define INVALIDSHADERHANDLE -1

class TSpriteShaderHAL;

class TSPRITESHADERD3D_EXPORTS TSpriteShaderOrderTable
{
public:
	TSpriteShaderOrderTable(TSpriteShaderHAL *a_pShader, TUINT a_uiRenderPackets, TUINT a_uiMaxRendPackets)
	{
		m_pShader          = a_pShader;
		m_uiMaxRendPackets = a_uiMaxRendPackets;
		m_uiNumRendPackets = a_uiRenderPackets;
		m_pRenderPackets   = new TRenderPacket[a_uiMaxRendPackets];
	}

	void           Render();
	TRenderPacket *AllocRenderPacket();

private:
	TSpriteShaderHAL *m_pShader;          // 0x0
	TUINT             m_uiMaxRendPackets; // 0x4
	TUINT             m_uiNumRendPackets; // 0x8
	TRenderPacket    *m_pRenderPackets;   // 0xC
};

class TSPRITESHADERD3D_EXPORTS TSpriteShaderHAL : public TSpriteShader
{
	DECLARE_DYNAMIC(TSpriteShaderHAL)

public:
	TSpriteShaderHAL()
		: m_oOrderTable(this, 1000, 5000)
	{
		m_dwVertexShaderHandle = INVALIDSHADERHANDLE;
		m_bMipMapLODBias       = TTRUE;
		m_pVertexPool          = TNULL;
	}

	TRenderD3DInterface *GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}

	DWORD GetVertexShaderHandle()
	{
		Validate();
		return m_dwVertexShaderHandle;
	}

	TVertexPoolResourceInterface *GetVertexPool()
	{
		return m_pVertexPool;
	}

	virtual TBOOL            Create();
	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName);
	virtual TSpriteMesh     *CreateMesh(TINT a_iCount, TINT &a_rMeshSize);
	virtual TBOOL            OnResetDevice();
	virtual void             Flush();
	virtual void             Render(TRenderPacket *a_pRenderPacket);
	virtual TBOOL            Validate();
	virtual void             BeginMeshGeneration();
	virtual void             EndMeshGeneration();

protected:
	TBOOL SupportMipMapLODBias();

public:
	static const DWORD SHADERDECL[];

private:
	TINT                    m_iNumVertices;         // 0x114
	TSpriteMaterial        *m_pLineMaterial;        // 0x118
	TSpriteMaterial        *m_pFillMaterial;        // 0x11C
	DWORD                   m_dwVertexShaderHandle; // 0x128
	TSpriteShaderOrderTable m_oOrderTable;          // 0x130
	TVertexPoolResource    *m_pVertexPool;          // 0x140
	TBOOL                   m_bMipMapLODBias;       // 0x148
};

class TSPRITESHADERD3D_EXPORTS TSpriteMaterialHAL : public TSpriteMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterialHAL)
public:

	TSpriteMaterialHAL()
	{
		m_pTexture = TNULL;
	}

	TRenderD3DInterface* GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}

	virtual void PreRender() override;
	virtual void PostRender() override;
};

class TSPRITESHADERD3D_EXPORTS TSpriteMeshHAL : public TSpriteMesh
{
	DECLARE_DYNAMIC(TSpriteMeshHAL)

	virtual TBOOL Create(TUINT a_uiFlags, TUSHORT a_usX, TUSHORT a_usY);
	virtual TBOOL Render();

public:
	TSpriteShaderHAL* GetShader()
	{
		return static_cast<TSpriteShaderHAL *>(TMesh::GetShader());
	}
};

TOSHI_NAMESPACE_END
