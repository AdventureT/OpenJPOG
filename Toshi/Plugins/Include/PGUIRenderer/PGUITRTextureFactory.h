#pragma once
#include "Defines.h"
#include "TGui/TGUITextureFactory.h"
#include "TKernel/TPCString.h"

class PGUIRENDERER_EXPORTS PGUITRTextureFactory : public Toshi::TGUITextureFactory
{
	DECLARE_DYNAMIC(PGUITRTextureFactory)

public:

	enum TextureFlag
	{

	};

	class Texture
	{
	public:

		Texture(const Toshi::TPCString &a_rName, PGUITRTextureFactory *a_pTextureFactory, TBOOL a_bValidate)
		{
			m_sName           = a_rName;
			m_pTextureFactory = a_pTextureFactory;
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
		const Toshi::TPCString& GetName() const
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
		}

	private:
		Toshi::TPCString m_sName; // 0x0
		PGUITRTextureFactory *m_pTextureFactory; // 0x4
		TINT             m_iWidth; // 0x10
		TINT  m_iHeight; // 0x14
		TUINT m_eFlags; // 0x18
	};
};
