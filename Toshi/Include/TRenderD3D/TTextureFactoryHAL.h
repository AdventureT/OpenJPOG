#pragma once

#include "TRender/TResource.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TTextureFactoryHAL
{
public:

	enum TTEXTURERESOURCEFORMAT
	{

	};

	virtual TTextureResource* CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, BOOL a_bNoMipLevels)
	{
		return TNULL;
	}

};

TOSHI_NAMESPACE_END