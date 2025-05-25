#include "TRenderD3D/TTextureFactoryD3D.h"
#include "TRender/TRenderInterface.h"
#include "TRenderD3D/TTextureResourceD3D.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TTextureFactoryHAL, TTextureFactory)

// $TRenderD3DInterface: FUNCTION 1000c400
TTextureResource *TTextureFactoryHAL::CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	TTextureResource *pTexture = FindTexture(a_szFileName);

	if (pTexture) return pTexture;

	pTexture = TSTATICCAST(
		TTextureResource *,
		GetRenderer()->CreateResource(
			TClass::Find("TTextureResourceHAL", TNULL),
			TNULL,
			this));

	pTexture->Create(a_szFileName, a_eTextureFlags);
	RegisterTexture(a_szFileName, pTexture);
	pTexture->Validate();

	return pTexture;
}

// $TRenderD3DInterface: FUNCTION 1000c480
TTextureResource *TTextureFactoryHAL::CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels)
{
	static TUINT s_iNumMemTextures = 0;
	static char  s_szName[32];

	s_szName[0] = 'm';
	s_szName[1] = 't';
	s_szName[2] = 'e';
	s_szName[3] = 'x';
	s_szName[4] = ':';

	TSystem::StringIntToString(++s_iNumMemTextures, &s_szName[5], 16);
	TTextureResource *pTexture = TSTATICCAST(
		TTextureResource *,
		GetRenderer()->CreateResource(
			TClass::Find("TTextureResourceHAL", TNULL),
			TNULL,
			this));

	pTexture->Create(a_pData, a_uiDataSize, a_uiWidth, a_uiHeight, a_uiMipLevels);
	RegisterTexture(s_szName, pTexture);

	return pTexture;
}

// $TRenderD3DInterface: FUNCTION 1000c530
TTextureResource *TTextureFactoryHAL::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiFormatBits)
{
	static TUINT s_iNumMemTextures = 0;
	static char  s_szName[32];

	s_szName[0] = 'm';
	s_szName[1] = 't';
	s_szName[2] = 'e';
	s_szName[3] = 'x';
	s_szName[4] = ':';

	TSystem::StringIntToString(++s_iNumMemTextures, &s_szName[5], 16);
	TTextureResource *pTexture = TSTATICCAST(
		TTextureResource *,
		GetRenderer()->CreateResource(
			TClass::Find("TTextureResourceHAL", TNULL),
			TNULL,
			this));

	pTexture->CreateEx(a_pData, a_uiDataSize, a_uiWidth, a_uiHeight, a_uiMipLevels, a_eFormat, a_uiFormatBits);
	RegisterTexture(s_szName, pTexture);

	return pTexture;
}
