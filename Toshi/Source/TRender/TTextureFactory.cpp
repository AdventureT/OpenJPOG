#include "TTextureFactory.h"
#include "TTextureResource.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureFactory, TResource)

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
	TNodeList<TTextureFactory::NameEntry>* pList = &m_aLists[HashName(a_szName)];
	TTextureFactory::NameEntry* pEntry = new TTextureFactory::NameEntry(a_szName, a_pTexture);

	TVALIDADDRESS(a_pTexture->m_pNameEntry);
	a_pTexture->m_pNameEntry = pEntry;
	pList->InsertHead(*pEntry);

	return a_pTexture->m_pNameEntry;
}
