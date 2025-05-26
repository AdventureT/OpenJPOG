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
	enum ADDRESSMODE
	{
		ADDRESSMODE_WRAP,
		ADDRESSMODE_MIRROR,
		ADDRESSMODE_CLAMP,
		ADDRESSMODE_BORDER
	};

	struct LOCKSTATE
	{
		TINT   Pitch;
		TPVOID pBits;
	};

	TTextureResource();

	virtual ~TTextureResource();

	virtual TUINT GetWidth()  = 0;
	virtual TUINT GetHeight() = 0;
	virtual TBOOL Lock(LOCKSTATE &a_rLockState);
	virtual void  Unlock();
	virtual TBOOL Create(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_eTextureFlags, TUINT a_uiWidth, TUINT a_uiHeight) = 0;
	virtual TBOOL Create(TPCCHAR a_szFileName, TUINT a_eTextureFlags)                                                  = 0;
	virtual TBOOL CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiMipmapFlags);

	static TTextureResource *TOSHI_API CreateHAL(TRenderInterface *a_pRenderer, TPCCHAR a_szName, TResource *a_pResource);

public:
	// $TRenderInterface: FUNCTION 1000f3a0
	TTextureFactory::NameEntry *GetNameEntry() { return m_pNameEntry; }
	// $TRenderInterface: FUNCTION 1000f390
	TUINT                       GetCreateFlags() { return m_CreateFlags; }

	// $TRenderInterface: FUNCTION 1000f370
	ADDRESSMODE GetAddressMode()
	{
		return m_eAddressMode;
	}

	// $TRenderInterface: FUNCTION 1000f380
	ADDRESSMODE SetAddressModeMode(ADDRESSMODE a_eAddressMode)
	{
		m_eAddressMode = a_eAddressMode;
		return m_eAddressMode;
	}

private:
	ADDRESSMODE                 m_eAddressMode; // 0x30
	TUINT                       m_CreateFlags;  // 0x34
	TTextureFactory::NameEntry *m_pNameEntry;   // 0x38
};

TOSHI_NAMESPACE_END
