#pragma once
#include "Defines.h"
#include "TGui/TGUITextureFactory.h"
#include "TKernel/TPCString.h"
#include "TRender/TRenderInterface.h"
#include "TSpriteShader/Include/TSpriteShader.h"
#include "PGUIRenderer/PGUITRDisplayContext.h"

typedef TINT16 PGUITextureID;

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
		Texture(const Toshi::TPCString &a_rName, PGUITRTextureFactory *a_pTextureFactory, TBOOL a_bValidate);

		TINT GetHeight();
		TINT GetWidth();
		
		void Validate();
		void Invalidate();

		void SetFlag(TextureFlag a_eFlag, bool a_bEnable);
		TBOOL GetFlag(TextureFlag a_eFlag) const;

		const Toshi::TPCString &GetName() const;

	private:
		Toshi::TPCString        m_sName;           // 0x0
		PGUITRTextureFactory   *m_pTextureFactory; // 0x4
		Toshi::TSpriteMaterial *m_pMaterial;       // 0x8
		TINT                    m_iWidth;          // 0x10
		TINT                    m_iHeight;         // 0x14
		TUINT                   m_eFlags;          // 0x18
	};

	class TextureSet
	{
	public:
		using TextureNode = Toshi::TNodeListNodeWrapper<Texture>;

	public:
		TextureSet(PGUITRTextureFactory *a_pTextureFactory);

		void Add(TPCCHAR a_szTextureName);

		void Invalidate();
		void Validate();

	private:
		Toshi::TNodeList<TextureNode> m_listTextures;
		PGUITRTextureFactory         *m_pTextureFactory; // 0x10
	};

public:
	PGUITRTextureFactory();
	~PGUITRTextureFactory();

	virtual PGUITextureID GetTextureID(const Toshi::TPCString &a_rTextureName);
	virtual PGUITextureID FindTextureID(const Toshi::TPCString &a_rTextureName);
	virtual PGUITextureID ReserveTextureID(const Toshi::TPCString &a_rTextureName);
	virtual Toshi::TTextureResource *LoadTTexture(const Toshi::TPCString &a_sFileName, int &a_iWidth, int &a_iHeight);

	void Create(PGUITRDisplayContext *a_pDisplayContext);

	Texture *GetTexture(PGUITextureID a_iID);

	void DestroyTexture(PGUITextureID a_iID);

protected:
	PGUITextureID AllocatedTextureID();

protected:
	// [5/26/2025 InfiniteC0re]
	// Commented m_oTextureSet since it's probably storing something else, not TextureSet
	// Toshi::TArray<TextureSet> m_oTextureSet; // 0x4
	Texture **m_ppTextures;          // 0x0
	TINT      m_iTextureCapacity;    // 0x4
	TINT      m_iTextureCount;       // 0x8
	TINT      m_iTextureAllocations; // 0xC


	// ...
	PGUITRDisplayContext *m_pDisplayContext; // 0x1C
};
