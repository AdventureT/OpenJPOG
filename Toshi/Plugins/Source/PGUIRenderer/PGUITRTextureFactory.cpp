#include "PGUIRenderer/PGUITRTextureFactory.h"
#include "TRender/TTextureResource.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

IMPLEMENT_DYNCREATE(PGUITRTextureFactory, Toshi::TGUITextureFactory);

// $PGUIRenderer: FUNCTION 100068e0
PGUITRTextureFactory::PGUITRTextureFactory()
	: m_ppTextures(TNULL), m_iTextureCount(0), m_iTextureCapacity(10), m_iTextureAllocations(0)
{
}

// $PGUIRenderer: FUNCTION 10007da0
PGUITRTextureFactory::~PGUITRTextureFactory()
{
}

// $PGUIRenderer: FUNCTION 10007c60
void PGUITRTextureFactory::Create(PGUITRDisplayContext *a_pDisplayContext)
{
	m_pDisplayContext = a_pDisplayContext;

	if (m_iTextureCapacity < 200) {
		Texture **newTextures = new Texture *[200];
		if (!newTextures) {
			if (m_ppTextures) {
				delete[] m_ppTextures;
				m_ppTextures = TNULL;
			}
			m_iTextureCount    = 0;
			m_iTextureCapacity = 0;
			return;
		}
		if (m_ppTextures) {
			Toshi::TSystem::MemCopy(newTextures, m_ppTextures, m_iTextureCount * sizeof(Texture *));
			delete[] m_ppTextures;
		}
		m_ppTextures       = newTextures;
		m_iTextureCapacity = 200;
	}
	else {
		m_iTextureCount = 0;
	}
}

// $PGUIRenderer: FUNCTION 10006c40
PGUITRTextureFactory::Texture *PGUITRTextureFactory::GetTexture(PGUITextureID a_iID)
{
	// [5/26/2025 InfiniteC0re]
	// TODO: Add some assert message to make sure no buffer over-read happens
	return m_ppTextures[a_iID];
}

// $PGUIRenderer: FUNCTION 10006a80
void PGUITRTextureFactory::DestroyTexture(PGUITextureID a_iID)
{
	Texture *texture = GetTexture(a_iID);
	if (texture) {
		delete texture;
	}
	m_ppTextures[a_iID] = TNULL;
}

// $PGUIRenderer: FUNCTION 100070e0
PGUITextureID PGUITRTextureFactory::AllocatedTextureID()
{
	for (PGUITextureID id = 0; id < m_iTextureCount; id++) {
		if (m_ppTextures[id] == TNULL) {
			return id;
		}
	}
	if (m_iTextureCount + 1 > m_iTextureCapacity) {
		TINT      newCapacity = TMAX(m_iTextureCapacity + m_iTextureAllocations, m_iTextureCount + 1);
		Texture **newTextures = new Texture *[newCapacity];
		if (!newTextures) {
			if (m_ppTextures) {
				delete[] m_ppTextures;
			}
			m_iTextureCount    = 0;
			m_iTextureCapacity = 0;
			m_ppTextures       = TNULL;
			return -1;
		}
		if (m_ppTextures) {
			Toshi::TSystem::MemCopy(newTextures, m_ppTextures, m_iTextureCount * sizeof(Texture *));
			delete[] m_ppTextures;
		}
		for (TINT i = m_iTextureCount; i < newCapacity; i++) {
			newTextures[i] = TNULL;
		}
		m_ppTextures       = newTextures;
		m_iTextureCapacity = newCapacity;
	}
	return m_iTextureCount++;
}

// $PGUIRenderer: FUNCTION 10006b20
PGUITextureID PGUITRTextureFactory::GetTextureID(const Toshi::TPCString &a_rTextureName)
{
	PGUITextureID textureID = FindTextureID(a_rTextureName);
	if (textureID == -1) {
		textureID               = AllocatedTextureID();
		m_ppTextures[textureID] = new Texture(a_rTextureName, this, false);
	}
	return textureID;
}

// $PGUIRenderer: FUNCTION 10006b80
PGUITextureID PGUITRTextureFactory::FindTextureID(const Toshi::TPCString &a_rTextureName)
{
	PGUITextureID textureID = m_iTextureCount == 0 ? -1 : 0;
	for (; textureID < m_iTextureCount; textureID++) {
		Texture *texture = m_ppTextures[textureID];
		if (texture && texture->GetName() == a_rTextureName) {
			break;
		}
	}
	return textureID;
}

// $PGUIRenderer: FUNCTION 10006ac0
PGUITextureID PGUITRTextureFactory::ReserveTextureID(const Toshi::TPCString &a_rTextureName)
{
	return 0;
}

Toshi::TTextureResource *PGUITRTextureFactory::LoadTTexture(const Toshi::TPCString &a_sFileName, int &a_iWidth, int &a_iHeight)
{
	return TNULL;
}

// $PGUIRenderer: FUNCTION 10007770
PGUITRTextureFactory::Texture::Texture(const Toshi::TPCString &a_rName, PGUITRTextureFactory *a_pTextureFactory, TBOOL a_bValidate)
{
	m_sName           = a_rName;
	m_pTextureFactory = a_pTextureFactory;
	m_pMaterial       = TNULL;
	m_iWidth          = -1;
	m_iHeight         = -1;
}

// $PGUIRenderer: FUNCTION 10007b20
TBOOL PGUITRTextureFactory::Texture::GetFlag(TextureFlag a_eFlag) const
{
	return (m_eFlags & a_eFlag) != 0;
}

// $PGUIRenderer: FUNCTION 10005cc0
TINT PGUITRTextureFactory::Texture::GetHeight()
{
	return m_iHeight;
}

// $PGUIRenderer: FUNCTION 10007b40
const Toshi::TPCString &PGUITRTextureFactory::Texture::GetName() const
{
	return m_sName;
}

// $PGUIRenderer: FUNCTION 10005cd0
TINT PGUITRTextureFactory::Texture::GetWidth()
{
	return m_iWidth;
}

// $PGUIRenderer: FUNCTION 10007b00
void PGUITRTextureFactory::Texture::SetFlag(TextureFlag a_eFlag, TBOOL a_bEnable)
{
	if (a_bEnable) {
		m_eFlags |= a_eFlag;
	}
	else {
		m_eFlags &= a_eFlag;
	}
}

// $PGUIRenderer: FUNCTION 10007810
void PGUITRTextureFactory::Texture::Validate()
{
	if (!m_sName || m_sName->IsEmpty()) {
		return;
	}

	static const Toshi::TClass *s_pAllowedClass = Toshi::TClass::Find("TSpriteMaterialHAL", TNULL);
	Toshi::TMaterial           *pMaterial       = Toshi::TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->GetMaterial(*m_sName);

	if (!pMaterial || !pMaterial->IsA(*s_pAllowedClass)) {
		m_pMaterial = TNULL;
		return;
	}

	m_pMaterial = TSTATICCAST(Toshi::TSpriteMaterial *, pMaterial);
}

// $PGUIRenderer: FUNCTION 100078e0
void PGUITRTextureFactory::Texture::Invalidate()
{
}

// $PGUIRenderer: FUNCTION 10005c80
PGUITRTextureFactory::TextureSet::TextureSet(PGUITRTextureFactory *a_pTextureFactory)
	: m_pTextureFactory(a_pTextureFactory)
{
}

// $PGUIRenderer: FUNCTION 10007930
void PGUITRTextureFactory::TextureSet::Add(TPCCHAR a_szTextureName)
{
	Toshi::TPCString textureName = Toshi::TSystem::GetCStringPool()->Get(a_szTextureName);
	PGUITextureID    sTextureID  = m_pTextureFactory->ReserveTextureID(textureName);

	TextureNode *textureNode = new TextureNode(m_pTextureFactory->GetTexture(sTextureID));
	m_listTextures.InsertTail(*textureNode);
}

// $PGUIRenderer: FUNCTION 10007a00
void PGUITRTextureFactory::TextureSet::Invalidate()
{
	T_FOREACH (m_listTextures, node) {
		(*node)->Validate();
	}
}

// $PGUIRenderer: FUNCTION 100079c0
void PGUITRTextureFactory::TextureSet::Validate()
{
	T_FOREACH (m_listTextures, node) {
		(*node)->Invalidate();
	}
}
