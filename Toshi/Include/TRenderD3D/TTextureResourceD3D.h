#pragma once
#include "TRender/TTextureResource.h"
#include "Defines.h"
#include "TKernel/TFreeList.h"
#include <d3dx8tex.h>

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TTextureResourceHAL : public TTextureResource
{
	DECLARE_DYNAMIC(TTextureResourceHAL)
	DECLARE_FREELIST(TTextureResourceHAL)

	enum MIPMAPFLAGS
	{
		MIPMAPFLAGS_DISABLED = BITFIELD(0)
	};

public:
	virtual ~TTextureResourceHAL() = default;

	virtual TBOOL Validate() override;
	virtual void  Invalidate() override;

	virtual TUINT GetWidth() override;
	virtual TUINT GetHeight() override;
	virtual TBOOL Lock(TTextureResource::LOCKSTATE &a_rLockState) override;
	virtual void  Unlock() override;
	virtual TBOOL Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight) override;
	virtual TBOOL Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags) override;
	virtual TBOOL CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags) override;

private:
	TBOOL CreateFromFormat();
	TBOOL CreateFromPPM(TPCCHAR)
	{
		TASSERT(!"SLS: Yet to do!\n");
		return TFALSE;
	}
	TBOOL CreateFromMemory8888(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData);
	TBOOL CreateFromMemory888(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData);
	TBOOL CreateFromMemory5551(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData);
	TBOOL CreateFromMemoryDDS(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData);
	TBOOL CreateFromMemory4444(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData);

protected:
	TBOOL IsPPM(TPCCHAR a_pFileName);

public:
	// $TRenderD3DInterface: FUNCTION 10004880
	IDirect3DTexture8 *GetD3DTexture() { return m_pD3DTexture; }

private:
	TUINT                  m_eTextureFlags;   // 0x34
	TUINT                  m_uiLockCount;     // 0x3C
	TINT                   m_iLoadFromMemory; // 0x40
	TPVOID                 m_pData;           // 0x44
	TUINT                  m_uiDataSize;      // 0x48
	TUINT                  m_uiWidth;         // 0x4C
	TUINT                  m_uiHeight;        // 0x50
	TINT                   m_uiMipLevels;     // 0x54
	TUINT                  m_uiMipmapFlags;   // 0x58
	TTEXTURERESOURCEFORMAT m_eResourceFormat; // 0x5C
	IDirect3DTexture8     *m_pD3DTexture;     // 0x60
	D3DXIMAGE_INFO         m_oImageInfo;      // 0x64
};

TOSHI_NAMESPACE_END
