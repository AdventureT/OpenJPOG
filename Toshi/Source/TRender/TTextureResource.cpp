#include "TTextureResource.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureResource, TResource)

TBOOL TTextureResource::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags)
{
	return TResource::Create();
}
