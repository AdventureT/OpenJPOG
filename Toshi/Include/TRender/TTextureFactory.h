#pragma once

#include "TKernel/TObject.h"
#include "TKernel/TNodeList.h"
#include "TKernel/TSystemTools.h"
#include "Defines.h"
#include "TRender/TResource.h"

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;
class TTextureResource;

enum TTEXTURERESOURCEFORMAT
{
	UNKNOWN,
	R8G8B8A8,
	R8G8B8,
	R5G5B5A1,
	DDS,
	R4G4B4A4,
};

class TRENDERINTERFACE_EXPORTS TTextureFactory : public TResource
{
	DECLARE_DYNAMIC(TTextureFactory)

public:
	class NameEntry : public TNodeList<NameEntry>::TNode
	{
	public:
		NameEntry(TPCCHAR a_szName, TTextureResource* a_pTexture)
		{
			m_pTexture = a_pTexture;

			if (TSystem::StringLength(a_szName) < MAX_TEXTURENAMELEN) {
				TSystem::StringCopy(m_szName, a_szName, MAX_TEXTURENAMELEN);
			}
			else {
				TASSERT(1 < MAX_TEXTURENAMELEN);
				*m_szName = '\0';
			}
		}
		~NameEntry()
		{
			TASSERT(IsLinked()==TFALSE);
		}

		TPCCHAR GetName() const { return m_szName; }
		TTextureResource* GetTexture() { return m_pTexture; }

	private:

		static constexpr TUINT32 MAX_TEXTURENAMELEN = 50;

		TCHAR m_szName[MAX_TEXTURENAMELEN];
		TTextureResource* m_pTexture;
	};

public:

	virtual TTextureResource* CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags) = 0;
	virtual TTextureResource* CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels) = 0;
	virtual TTextureResource* CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiFormatBits) = 0;

	static TTextureFactory* TOSHI_API CreateHAL(TRenderInterface* a_pRenderer, TPCCHAR a_szName, TResource* a_pResource);

	TTextureResource* FindTexture(TPCCHAR a_szName);

protected:

	TUINT HashName(TPCCHAR a_szName);

	TTextureFactory::NameEntry* RegisterTexture(TPCCHAR a_szName, TTextureResource* a_pResource);

private:

	static constexpr TUINT32 NUM_LISTS = 1024;

	TNodeList<NameEntry> m_aLists[NUM_LISTS];
};

TOSHI_NAMESPACE_END