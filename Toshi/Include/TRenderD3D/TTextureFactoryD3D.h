#pragma once
#include "Defines.h"
#include "TRender/TResource.h"
#include "TRender/TTextureFactory.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TTextureFactoryHAL : public TTextureFactory
{
	DECLARE_DYNAMIC(TTextureFactoryHAL)

public:

	virtual TTextureResource* CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags) override;
	virtual TTextureResource* CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels) override;
	virtual TTextureResource* CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiFormatBits) override;

};

TOSHI_NAMESPACE_END