#pragma once
#include "Defines.h"
#include "../TSpriteShader.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"
#include "TRenderD3D/TOrderTable.h"
#include "TRenderD3D/TD3DVertexPoolResource.h"
#include "TRenderD3D/TD3DIndexPoolResource.h"

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
		m_uiNumRendPackets = 0;
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
	// $TSpriteShaderD3D: FUNCTION 10002610
	TSpriteShaderHAL()
		: m_oOrderTable(this, 1000, 5000)
	{
		m_dwVertexShaderHandle = INVALIDSHADERHANDLE;
		m_bVertexShaderSuccess = TTRUE;
		m_pVertexPool          = TNULL;
		m_pIndexPool           = TNULL;
		m_bMipMapLODBias       = TTRUE;
	}
	// $TSpriteShaderD3D: FUNCTION 10003990
	TRenderD3DInterface *GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}
	// $TSpriteShaderD3D: FUNCTION 100035c0
	DWORD GetVertexShaderHandle()
	{
		Validate();
		return m_dwVertexShaderHandle;
	}
	// $TSpriteShaderD3D: FUNCTION 10003960
	TVertexPoolResourceInterface *GetVertexPool()
	{
		return m_pVertexPool;
	}
	// $TSpriteShaderD3D: FUNCTION 10003950
	TIndexPoolResourceInterface *GetIndexPool()
	{
		return m_pIndexPool;
	}
	// $TSpriteShaderD3D: FUNCTION 10003970
	TSpriteShaderOrderTable *GetOrderTable()
	{
		return &m_oOrderTable;
	}

	virtual TBOOL            Create();
	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName);
	virtual TSpriteMesh     *CreateMesh(TINT a_iCount, TINT &a_rMeshSize);
	virtual TSpriteMesh     *CreateMesh(TPCCHAR a_szName);
	virtual TBOOL            OnResetDevice();
	virtual void             Flush();
	virtual void             Render(TRenderPacket *a_pRenderPacket);
	virtual TBOOL            Validate();
	virtual void             Invalidate();
	virtual void             SetMaterial(TSpriteMaterial *a_pMaterial);
	virtual void             BeginMeshGeneration();
	virtual void             EndMeshGeneration();

protected:
	TBOOL SupportMipMapLODBias();

public:
	static const DWORD SHADERDECL[];

private:
	DWORD                   m_dwVertexShaderHandle; // 0x128
	TBOOL                   m_bVertexShaderSuccess; // 0x12C
	TSpriteShaderOrderTable m_oOrderTable;          // 0x130
	TVertexPoolResource    *m_pVertexPool;          // 0x140
	TIndexPoolResource     *m_pIndexPool;            // 0x144
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
	// $TSpriteShaderD3D: FUNCTION 10003940
	TRenderD3DInterface* GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}
	// $TSpriteShaderD3D: FUNCTION 10003930
	TSpriteShaderHAL *GetShader() const
	{
		return TSTATICCAST(TSpriteShaderHAL *, m_pOwnerShader);
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
	// $TSpriteShaderD3D: FUNCTION 100038e0
	TSpriteShaderHAL* GetShader()
	{
		return static_cast<TSpriteShaderHAL *>(TSpriteMesh::GetShader());
	}
	// $TSpriteShaderD3D: FUNCTION 100038d0
	TSpriteMaterialHAL *GetMaterial()
	{
		return static_cast<TSpriteMaterialHAL *>(TSpriteMesh::GetMaterial());
	}
};

TOSHI_NAMESPACE_END
