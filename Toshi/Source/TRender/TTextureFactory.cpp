#include "TTextureFactory.h"
#include "TRender/TRenderInterface.h"
#include "TTextureResource.h"


TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureFactory, TResource)

TTextureResource* TTextureFactory::CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	return TNULL;
}

TTextureResource* TTextureFactory::CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels)
{
	return TNULL;
}

TTextureResource* TTextureFactory::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiFormatBits)
{
	return TNULL;
}

TTextureFactory* TOSHI_API TTextureFactory::CreateHAL(TRenderInterface* a_pRenderer, TPCCHAR a_szName, TResource* a_pResource)
{
	return (TTextureFactory*)a_pRenderer->CreateResource(TClass::Find("TTextureFactoryHAL", TNULL), a_szName, a_pResource);
}

TTextureResource* TTextureFactory::FindTexture(TPCCHAR a_szName)
{
	auto pList = &m_aLists[HashName(a_szName)];

	for (auto it = pList->Begin(); it != pList->End(); it++)
	{
		if (0 == TSystem::StringCompareNoCase(it->GetName(), a_szName, -1))
		{
			return it->GetTexture();
		}
	}

	return TNULL;
}

TUINT TTextureFactory::HashName(TPCCHAR a_szName)
{
	TUINT iHash = 0;

	for (size_t i = 0; i < TSystem::StringLength(a_szName); i++)
	{
		iHash += a_szName[i];
	}

	return iHash % NUM_LISTS;
}

TTextureFactory::NameEntry* TTextureFactory::RegisterTexture(TPCCHAR a_szName, TTextureResource* a_pTexture)
{
	auto pList = &m_aLists[HashName(a_szName)];
	auto pEntry = new TTextureFactory::NameEntry(a_szName, a_pTexture);

	a_pTexture->m_pNameEntry = pEntry;
	TVALIDADDRESS(a_pTexture->m_pNameEntry);
	pList->InsertHead(*pEntry);

	return a_pTexture->m_pNameEntry;
}
