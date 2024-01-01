#include "TTextureResource.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureResource, TResource)

TBOOL TTextureResource::Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight)
{
	return TTRUE;
}

TBOOL TTextureResource::Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	return TTRUE;
}

TBOOL TTextureResource::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags)
{
	return TResource::Create();
}
