#include "TRenderD3D/TTextureResourceD3D.h"
#include "TRenderD3D/TRenderD3DInterface.h"

#include <d3dtypes.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TTextureResourceHAL, TTextureResource)

TBOOL TTextureResourceHAL::Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight)
{
	TDPRINTF("Deprecated! Please use: TTextureResourceHAL::CreateEx()\n");
	if (!TTextureResource::Create(a_pData, a_uiDataSize, a_uiWidth, 0, 0)) {
		return TFALSE;
	}

	m_eTextureFlags = a_eTextureFlags;
	m_uiWidth = a_uiWidth;
	m_uiHeight = a_uiHeight;
	m_uiMipLevels = 0;
	m_eResourceFormat = UNKNOWN;
	m_uiMipmapFlags = MIPMAPFLAGS_DISABLED;
	m_iLoadFromMemory = 1;
	m_pData = a_pData;
	m_uiDataSize = a_uiDataSize;

	Validate();
	return TTRUE;
}

TBOOL TTextureResourceHAL::Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	if (!TTextureResource::Create(a_szFileName, a_eTextureFlags)) {
		return TFALSE;
	}

	m_eTextureFlags = a_eTextureFlags;
	m_uiMipmapFlags = MIPMAPFLAGS_DISABLED;

	return TTRUE;
}

TBOOL TTextureResourceHAL::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags)
{
	if (!TTextureResource::CreateEx(a_pData, a_uiDataSize, a_uiWidth, a_uiHeight, a_uiMipLevels, a_eFormat, a_uiMipmapFlags)) {
		return TFALSE;
	}

	m_eTextureFlags = 0x40;
	m_uiWidth = a_uiWidth;
	m_uiHeight = a_uiHeight;
	m_uiMipLevels = a_uiMipLevels;
	m_eResourceFormat = a_eFormat;
	m_uiMipmapFlags = a_uiMipmapFlags;
	m_iLoadFromMemory = 1;
	m_pData = a_pData;
	m_uiDataSize = a_uiDataSize;

	Validate();
	return TTRUE;
}

TBOOL TTextureResourceHAL::CreateFromFormat()
{
	TUINT uiMipLevels = (m_uiMipmapFlags & MIPMAPFLAGS_DISABLED) ? 0 : m_uiMipLevels;

	switch (m_eResourceFormat)
	{
	case TTEXTURERESOURCEFORMAT::R8G8B8A8:
		return CreateFromMemory8888(m_uiWidth, m_uiHeight, uiMipLevels, m_pData);
	case TTEXTURERESOURCEFORMAT::R8G8B8:
		return CreateFromMemory888(m_uiWidth, m_uiHeight, uiMipLevels, m_pData);
	case TTEXTURERESOURCEFORMAT::R5G5B5A1:
		return CreateFromMemory5551(m_uiWidth, m_uiHeight, uiMipLevels, m_pData);
	case TTEXTURERESOURCEFORMAT::DDS:
		return CreateFromMemoryDDS(m_uiWidth, m_uiHeight, uiMipLevels, m_pData);
	case TTEXTURERESOURCEFORMAT::R4G4B4A4:
		return CreateFromMemory4444(m_uiWidth, m_uiHeight, uiMipLevels, m_pData);
	default:
		TASSERT(!"Unknown format!\n");
		return TFALSE;
	}
}

TBOOL TTextureResourceHAL::CreateFromMemory8888(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData)
{
	TRenderD3DInterface* pRenderer = static_cast<TRenderD3DInterface*>(GetRenderer());

	HRESULT hCreateRes = pRenderer->GetD3DDevice()->CreateTexture(
		a_uiWidth,
		a_uiHeight,
		a_uiLevels,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pD3DTexture
	);
	TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

	if (SUCCEEDED(hCreateRes)) {
		D3DLOCKED_RECT rect;
		m_pD3DTexture->LockRect(0, &rect, NULL, D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK);
		TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

		if (a_uiHeight != 0) {
			TUINT8* pTexPixel = TSTATICCAST(TUINT8*, rect.pBits);
			TUINT8* pDataPixel = TSTATICCAST(TUINT8*, a_pData);

			for (TUINT i = a_uiHeight; i != 0; i--) {
				TUINT8 uiDataPixel = *pDataPixel;
				pTexPixel[0] = pDataPixel[3];
				pTexPixel[1] = pDataPixel[2];
				pTexPixel[2] = pDataPixel[1];
				pTexPixel[3] = pDataPixel[0];

				pTexPixel += 4;
				pDataPixel += 4;
			}

			m_pD3DTexture->UnlockRect(0);

			if (a_uiLevels == 0) {
				TSystem::MemSet(&m_oImageInfo, 0, sizeof(D3DXIMAGE_INFO));
				m_oImageInfo.Width = a_uiWidth;
				m_oImageInfo.Height = a_uiHeight;
			}
		}

	}

	return TTRUE;
}

TBOOL TTextureResourceHAL::CreateFromMemory888(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData)
{
	TRenderD3DInterface* pRenderer = static_cast<TRenderD3DInterface*>(GetRenderer());

	HRESULT hCreateRes = pRenderer->GetD3DDevice()->CreateTexture(
		a_uiWidth,
		a_uiHeight,
		a_uiLevels,
		0,
		D3DFMT_X8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pD3DTexture
	);
	TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

	if (SUCCEEDED(hCreateRes)) {
		D3DLOCKED_RECT rect;
		m_pD3DTexture->LockRect(0, &rect, NULL, D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK);
		TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

		if (a_uiHeight != 0) {
			TUINT8* pTexPixel = TSTATICCAST(TUINT8*, rect.pBits);
			TUINT8* pDataPixel = TSTATICCAST(TUINT8*, a_pData);

			for (TUINT i = a_uiHeight; i != 0; i--) {
				TUINT8 uiDataPixel = *pDataPixel;
				pTexPixel[0] = pDataPixel[2];
				pTexPixel[1] = pDataPixel[1];
				pTexPixel[2] = pDataPixel[0];
				pTexPixel[3] = 255;

				pTexPixel += 4;
				pDataPixel += 3;
			}

			m_pD3DTexture->UnlockRect(0);

			if (a_uiLevels == 0) {
				TSystem::MemSet(&m_oImageInfo, 0, sizeof(D3DXIMAGE_INFO));
				m_oImageInfo.Width = a_uiWidth;
				m_oImageInfo.Height = a_uiHeight;
			}
		}

	}

	return TBOOL();
}

TBOOL TTextureResourceHAL::CreateFromMemory5551(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData)
{
	return TBOOL();
}

TBOOL TTextureResourceHAL::CreateFromMemoryDDS(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData)
{
	auto pRenderer = TSTATICCAST(TRenderD3DInterface*, GetRenderer());

	HRESULT hRes = D3DXCreateTextureFromFileInMemoryEx(pRenderer->GetD3DDevice(), 
		a_pData, 
		m_uiDataSize, 
		-1, 
		-1, 
		a_uiLevels, 
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		-1,
		-1,
		0,
		&m_oImageInfo,
		NULL,
		&m_pD3DTexture);
	TRenderD3DInterface::TD3DAssert(hRes, TNULL);
	if (hRes == D3D_OK) {
		return TTRUE;
	}
	TASSERT(hRes == D3D_OK);
	return TFALSE;
}

TBOOL TTextureResourceHAL::CreateFromMemory4444(TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiLevels, TPVOID a_pData)
{
	auto pRenderer = TSTATICCAST(TRenderD3DInterface*, GetRenderer());

	HRESULT hCreateRes = pRenderer->GetD3DDevice()->CreateTexture(
		a_uiWidth,
		a_uiHeight,
		a_uiLevels,
		0,
		D3DFMT_A4R4G4B4,
		D3DPOOL_MANAGED,
		&m_pD3DTexture
	);
	TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

	if (SUCCEEDED(hCreateRes)) {
		D3DLOCKED_RECT rect;
		m_pD3DTexture->LockRect(0, &rect, NULL, D3DLOCK_NO_DIRTY_UPDATE | D3DLOCK_NOSYSLOCK);
		TRenderD3DInterface::TD3DAssert(hCreateRes, TNULL);

		if (a_uiHeight != 0) {
			TUSHORT* pTexPixel = TSTATICCAST(TUSHORT*, rect.pBits);
			TUSHORT* pDataPixel = TSTATICCAST(TUSHORT*, a_pData);

			for (TUINT i = a_uiHeight; i != 0; i--) {
				TUSHORT uiDataPixel = *pDataPixel;
				*pTexPixel = ((((uiDataPixel >> 12) << 4 | uiDataPixel & 15) << 4 | uiDataPixel >> 4 & 15) << 4) | uiDataPixel >> 8 & 15;
				pTexPixel++;
				pDataPixel++;
			}
		}

		m_pD3DTexture->UnlockRect(0);

		if (a_uiLevels == 0) {
			TSystem::MemSet(&m_oImageInfo, 0, sizeof(D3DXIMAGE_INFO));
			m_oImageInfo.Width = a_uiWidth;
			m_oImageInfo.Height = a_uiHeight;
		}

		return TTRUE;
	}

	return TTRUE;
}
