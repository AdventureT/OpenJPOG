#pragma once

#include "TKernel/TObject.h"
#include "TRenderInterface.h"
#include "TKernel/TNodeList.h"
#include "TKernel/TSystemTools.h"

TOSHI_NAMESPACE_BEGIN

class TTextureResource;

class TOSHI_EXPORT TTextureFactory : public TResource
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

	static TTextureFactory* TOSHI_API CreateHAL(TRenderInterface* a_pRenderer, TPCCHAR a_szName, TResource* a_pResource)
	{
		return (TTextureFactory*)a_pRenderer->CreateResource(TClass::Find("TTextureFactoryHAL", TNULL), a_szName, a_pResource);
	}

protected:

	TUINT HashName(TPCCHAR a_szName);

	TTextureFactory::NameEntry* RegisterTexture(TPCCHAR a_szName, TTextureResource* a_pResource);

private:

	static constexpr TUINT32 NUM_LISTS = 1024;

	TNodeList<NameEntry> m_aLists[NUM_LISTS];
};

TOSHI_NAMESPACE_END