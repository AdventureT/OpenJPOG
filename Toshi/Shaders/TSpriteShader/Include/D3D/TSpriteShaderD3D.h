#pragma once
#include "Defines.h"
#include "../TSpriteShader.h"
#include "TRenderD3D/TRenderD3DInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"
#include "TRenderD3D/TOrderTable.h"

TOSHI_NAMESPACE_BEGIN

#define INVALIDSHADERHANDLE -1

class TSPRITESHADERD3D_EXPORTS TSpriteMaterialHAL : public TSpriteMaterial
{
	DECLARE_DYNAMIC(TSpriteMaterialHAL)
public:

	TSpriteMaterialHAL()
	{
		m_pTexture[0] = TNULL;
	}

	TRenderD3DInterface* GetRenderer() const
	{
		return TSTATICCAST(TRenderD3DInterface *, m_pRenderer);
	}

	virtual void PreRender() override;
	virtual void PostRender() override;
};

class TSPRITESHADERD3D_EXPORTS TSpriteMeshHAL
{
};

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

	void Render();

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

	virtual TSpriteMaterial *CreateMaterial(TPCCHAR a_szName);
	virtual void             Flush();
	virtual void             Render(TRenderPacket *a_pRenderPacket);
	virtual TBOOL            Validate();

protected:

	TBOOL SupportMipMapLODBias();

public:

	static const DWORD SHADERDECL[];

private:
	DWORD                   m_dwVertexShaderHandle; // 0x128
	TSpriteShaderOrderTable m_oOrderTable;          // 0x130
	TBOOL                   m_bMipMapLODBias;       // 0x148
};

TOSHI_NAMESPACE_END
