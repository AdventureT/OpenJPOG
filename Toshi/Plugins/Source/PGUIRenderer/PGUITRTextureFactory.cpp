#include "PGuiRenderer/PGUITRTextureFactory.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

IMPLEMENT_DYNCREATE(PGUITRTextureFactory, Toshi::TGUITextureFactory);

PGUITRTextureFactory::PGUITRTextureFactory()
	: m_ppTextures( TNULL )
{
}

PGUITRTextureFactory::~PGUITRTextureFactory()
{
}

void PGUITRTextureFactory::Create(PGUITRDisplayContext *a_pDisplayContext)
{
	m_pDisplayContext = a_pDisplayContext;
}

PGUITRTextureFactory::Texture *PGUITRTextureFactory::GetTexture(PGUITextureID a_iID)
{
	// [5/26/2025 InfiniteC0re]
	// TODO: Add some assert message to make sure no buffer over-read happens
	return m_ppTextures[a_iID];
}

PGUITextureID PGUITRTextureFactory::ReserveTextureID(const Toshi::TPCString &a_rTextureName)
{
	return 0;
}

PGUITRTextureFactory::Texture::Texture(const Toshi::TPCString &a_rName, PGUITRTextureFactory *a_pTextureFactory, TBOOL a_bValidate)
{
	m_sName           = a_rName;
	m_pTextureFactory = a_pTextureFactory;
	m_pMaterial       = TNULL;
	m_iWidth          = -1;
	m_iHeight         = -1;
}

TBOOL PGUITRTextureFactory::Texture::GetFlag(TextureFlag a_eFlag) const
{
	return (m_eFlags & a_eFlag) != 0;
}

TINT PGUITRTextureFactory::Texture::GetHeight()
{
	return m_iHeight;
}

const Toshi::TPCString &PGUITRTextureFactory::Texture::GetName() const
{
	return m_sName;
}

TINT PGUITRTextureFactory::Texture::GetWidth()
{
	return m_iWidth;
}

void PGUITRTextureFactory::Texture::SetFlag(TextureFlag a_eFlag, TBOOL a_bEnable)
{
	if (a_bEnable) {
		m_eFlags |= a_eFlag;
	}
	else {
		m_eFlags &= a_eFlag;
	}
}

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

void PGUITRTextureFactory::Texture::Invalidate()
{
}

PGUITRTextureFactory::TextureSet::TextureSet(PGUITRTextureFactory *a_pTextureFactory)
	: m_pTextureFactory(a_pTextureFactory)
{
}

void PGUITRTextureFactory::TextureSet::Add(TPCCHAR a_szTextureName)
{
	Toshi::TPCString textureName = Toshi::TSystem::GetCStringPool()->Get(a_szTextureName);
	PGUITextureID    sTextureID  = m_pTextureFactory->ReserveTextureID(textureName);

	TextureNode *textureNode = new TextureNode(m_pTextureFactory->GetTexture(sTextureID));
	m_listTextures.InsertTail(*textureNode);
}

void PGUITRTextureFactory::TextureSet::Invalidate()
{
	T_FOREACH (m_listTextures, node) {
		(*node)->Validate();
	}
}

void PGUITRTextureFactory::TextureSet::Validate()
{
	T_FOREACH (m_listTextures, node) {
		(*node)->Invalidate();
	}
}
