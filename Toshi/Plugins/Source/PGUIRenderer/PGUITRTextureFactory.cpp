#include "PGuiRenderer/PGUITRTextureFactory.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

IMPLEMENT_DYNCREATE(PGUITRTextureFactory, Toshi::TGUITextureFactory);

// $PGUIRenderer: FUNCTION 100068e0
PGUITRTextureFactory::PGUITRTextureFactory()
	: m_ppTextures( TNULL )
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
}

// $PGUIRenderer: FUNCTION 10006c40
PGUITRTextureFactory::Texture *PGUITRTextureFactory::GetTexture(PGUITextureID a_iID)
{
	// [5/26/2025 InfiniteC0re]
	// TODO: Add some assert message to make sure no buffer over-read happens
	return m_ppTextures[a_iID];
}

// $PGUIRenderer: FUNCTION 10006ac0
PGUITextureID PGUITRTextureFactory::ReserveTextureID(const Toshi::TPCString &a_rTextureName)
{
	return 0;
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
