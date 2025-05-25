#pragma once
#include "Defines.h"
#include "TGui/TGUITextureFactory.h"
#include "TKernel/TPCString.h"
#include "TRender/TRenderInterface.h"
#include "TSpriteShader/Include/TSpriteShader.h"
#include "PGUIRenderer/PGUITRDisplayContext.h"

class PGUIRENDERER_EXPORTS PGUITRTextureFactory : public Toshi::TGUITextureFactory
{
	DECLARE_DYNAMIC(PGUITRTextureFactory)

public:
	enum TextureFlag
	{

	};
	// inherits TNode? Does not align with disassembly
	class Texture : public Toshi::TNodeList<Texture>::TNode
	{
	public:
		Texture(const Toshi::TPCString &a_rName, PGUITRTextureFactory *a_pTextureFactory, TBOOL a_bValidate)
		{
			m_sName           = a_rName;
			m_pTextureFactory = a_pTextureFactory;
			m_pMaterial       = TNULL;
			m_iWidth          = -1;
			m_iHeight         = -1;
		}

		TBOOL GetFlag(TextureFlag a_eFlag) const
		{
			return (m_eFlags & a_eFlag) != 0;
		}
		TINT GetHeight()
		{
			return m_iHeight;
		}
		const Toshi::TPCString &GetName() const
		{
			return m_sName;
		}
		TINT GetWidth()
		{
			return m_iWidth;
		}

		void SetFlag(TextureFlag a_eFlag, bool a_bEnable)
		{
			if (a_bEnable) {
				m_eFlags |= a_eFlag;
			}
			else {
				m_eFlags &= a_eFlag;
			}
		}
		void Validate()
		{
			bool invalid = !m_sName || m_sName->IsEmpty();
			if (invalid) {
				return;
			}
			static const Toshi::TClass *s_pAllowedClass = Toshi::TClass::Find("TSpriteMaterialHAL", TNULL);
			Toshi::TMaterial *pMaterial = Toshi::TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->GetMaterial(*m_sName);
			if (!pMaterial || !pMaterial->IsA(*s_pAllowedClass)) {
				m_pMaterial = TNULL;
				return;
			}
			m_pMaterial = TSTATICCAST(Toshi::TSpriteMaterial *, pMaterial);

		}
		void Invalidate()
		{
		}

	private:
		Toshi::TPCString        m_sName;           // 0x0
		PGUITRTextureFactory   *m_pTextureFactory; // 0x4
		Toshi::TSpriteMaterial *m_pMaterial;       // 0x8
		TINT                    m_iWidth;          // 0x10
		TINT                    m_iHeight;         // 0x14
		TUINT                   m_eFlags;          // 0x18
	};

	class TextureSet : public Toshi::TNodeList<Texture>
	{
	public:
		TextureSet(PGUITRTextureFactory *a_pTextureFactory)
		{
			m_pTextureFactory = a_pTextureFactory;
		}
		// Revisit this, not sure if it lines up with the disassembly
		void Add(TPCCHAR a_szTextureName)
		{
			Toshi::TPCString textureName = Toshi::TSystem::GetCStringPool()->Get(a_szTextureName);
			short            sTextureID  = m_pTextureFactory->ReserveTextureID(textureName);
			Texture         *texture     = new Texture(textureName, m_pTextureFactory, true);
			m_pTextureFactory->m_oTextureSet[sTextureID].InsertTail(*texture);
		}
		void Invalidate()
		{
			for (auto node = Begin(); node != End(); node++) {
				node->Validate();
			}
		}
		void Validate()
		{
			for (auto node = Begin(); node != End(); node++) {
				node->Invalidate();
			}
		}
	private:
		PGUITRTextureFactory     *m_pTextureFactory; // 0x10
	};

	void Create(PGUITRDisplayContext *a_pDisplayContext);

	virtual short ReserveTextureID(const Toshi::TPCString &a_rTextureName);

	Toshi::TArray<TextureSet> m_oTextureSet; // 0x4
	PGUITRDisplayContext *m_pDisplayContext; // 0x1C
};
