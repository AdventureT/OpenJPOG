#include "TTextureFactory.h"
#include "TTextureResource.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureFactory, TResource)



TUINT TTextureFactory::HashName(TPCCHAR a_szName)
{
	return TUINT();
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
