#include "TTextureFactory.h"
#include "TRender/TRenderInterface.h"
#include "TTextureResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TTextureFactory, TResource)

TTextureResource *TTextureFactory::CreateTextureFromFile(TPCCHAR a_szFileName, TUINT a_eTextureFlags)
{
	return TNULL;
}

TTextureResource *TTextureFactory::CreateTextureFromMemory(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels)
{
	return TNULL;
}

TTextureResource *TTextureFactory::CreateEx(TPVOID a_pData, TUINT a_uiDataSize, TUINT a_uiWidth, TUINT a_uiHeight, TUINT a_uiMipLevels, TTEXTURERESOURCEFORMAT a_eFormat, TUINT a_uiFormatBits)
{
	return TNULL;
}

// $TRenderInterface: FUNCTION 1000f4c0
TTextureFactory *TOSHI_API TTextureFactory::CreateHAL(TRenderInterface *a_pRenderer, TPCCHAR a_szName, TResource *a_pResource)
{
	return (TTextureFactory *)a_pRenderer->CreateResource(TClass::Find("TTextureFactoryHAL", TNULL), a_szName, a_pResource);
}

// $TRenderInterface: FUNCTION 10011b90
TTextureResource *TTextureFactory::FindTexture(TPCCHAR a_szName)
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

// $TRenderInterface: FUNCTION 10011c70
void TTextureFactory::DeregisterTexture(TTextureResource *a_pTexture)
{
	TVALIDADDRESS(a_pTexture);

	TNodeList<TTextureFactory::NameEntry> *pList = a_pTexture->m_pNameEntry->GetList();

	if (pList) {
		delete pList->Remove(*a_pTexture->m_pNameEntry);
	}
}

// $TRenderInterface: FUNCTION 10011d90
TUINT TTextureFactory::HashName(TPCCHAR a_szName)
{
	TUINT iHash = 0;

	for (TINT i = 0; i < TSystem::StringLength(a_szName); i++)
	{
		iHash += a_szName[i];
	}

	return iHash % NUM_LISTS;
}

// $TRenderInterface: FUNCTION 10011e10
TTextureFactory::NameEntry *TTextureFactory::RegisterTexture(TPCCHAR a_szName, TTextureResource *a_pTexture)
{
	auto pList  = &m_aLists[HashName(a_szName)];
	auto pEntry = new TTextureFactory::NameEntry(a_szName, a_pTexture);

	a_pTexture->m_pNameEntry = pEntry;
	TVALIDADDRESS(a_pTexture->m_pNameEntry);
	pList->InsertHead(*pEntry);

	return a_pTexture->m_pNameEntry;
}
