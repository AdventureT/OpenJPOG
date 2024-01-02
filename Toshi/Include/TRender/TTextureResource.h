#pragma once

#include "TKernel/TDebug.h"
#include "TRender/TResource.h"
#include "TTextureFactory.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TTextureResource : public TResource
{
	DECLARE_DYNAMIC(TTextureResource)

	friend class TTextureFactory;
	friend class TTextureFactoryHAL;

public:

	virtual TBOOL Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight) = 0;
	virtual TBOOL Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags) = 0;
	virtual TBOOL CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags);

public:

	TTextureFactory::NameEntry* GetNameEntry() { return m_pNameEntry; }

private:
	TTextureFactory::NameEntry* m_pNameEntry;
};

TOSHI_NAMESPACE_END