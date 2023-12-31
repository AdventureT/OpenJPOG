#pragma once

#include "TRender/TResource.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TTextureFactoryHAL : public TTextureFactory
{
	DECLARE_DYNAMIC(TTextureFactoryHAL)

public:

	virtual TTextureResource* CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags);
	virtual TTextureResource* CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels);

	virtual TTextureResource* CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, BOOL a_bNoMipLevels);

};

TOSHI_NAMESPACE_END