#include "TTextureResource.h"
#include "TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureResource, TResource)

// $TRenderInterface: FUNCTION 10012460
TTextureResource::TTextureResource()
{
	m_eAddressMode = ADDRESSMODE_WRAP;
	m_CreateFlags  = 0;
	m_pNameEntry   = TNULL;
}

// $TRenderInterface: FUNCTION 100122d0
TTextureResource::~TTextureResource()
{
	TRenderInterface *pRenderer = TRenderInterface::GetRenderer();
	TVALIDADDRESS(pRenderer);
	TTextureFactory *pTextureFactory = (TTextureFactory *)pRenderer->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY);
	TVALIDADDRESS(pTextureFactory);
	pTextureFactory->DeregisterTexture(this);
}

TUINT TTextureResource::GetWidth()
{
	return 0;
}

TUINT TTextureResource::GetHeight()
{
	return 0;
}

// $TRenderInterface: FUNCTION 10012450
TBOOL TTextureResource::Lock(LOCKSTATE &a_rLockState)
{
	return TFALSE;
}

// $TRenderInterface: FUNCTION 10012440
void TTextureResource::Unlock()
{
}

TBOOL TTextureResource::Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight)
{
	return TResource::Create();
}

TBOOL TTextureResource::Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	return TResource::Create();
}

// $TRenderInterface: FUNCTION 10012410
TBOOL TTextureResource::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags)
{
	return TResource::Create();
}

// $TRenderInterface: FUNCTION 1000f3b0
TTextureResource *TOSHI_API TTextureResource::CreateHAL(TRenderInterface *a_pRenderer, TPCCHAR a_szName, TResource *a_pResource)
{
	return (TTextureResource *)a_pRenderer->CreateResource(TFindClass(TTextureResourceHAL, TNULL), a_szName, a_pResource);
}
