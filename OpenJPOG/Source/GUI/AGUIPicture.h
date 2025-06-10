#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TVector2.h"
#include "TSpriteShader/Include/TSpriteShader.h"

class AGUIPicture : public Toshi::TObject
{
	DECLARE_DYNAMIC(AGUIPicture, Toshi::TObject);

public:

	AGUIPicture();

	struct Tile
	{
		Toshi::TVector2 pos1;
		Toshi::TVector2 pos2;
		Toshi::TVector2 uv1;
		Toshi::TVector2 uv2;
		Toshi::TSpriteMaterial **ppMaterial;
	};

	struct Texture
	{
		Toshi::TSpriteMaterial *pMaterial;
		Toshi::TSpriteMesh *pTexture;
	};

	struct SplitRule
	{
		Toshi::TVector2 pos1;
		Toshi::TVector2 pos2;
		Toshi::TVector2 uv1;
		Toshi::TVector2 uv2;
		TINT            index;
		TINT            unk;
		TINT            unk2;
	};

public:

	virtual void Delete();
	virtual void Create(TPCCHAR a_szFileName, Toshi::TSpriteShader *a_pShader);
	virtual void Render();
	virtual void Flush() = 0;
	virtual void Cache() = 0;

public:
	// $JPOG: FUNCTION 00673160
	const Toshi::TCString& GetFileName()
	{
		return m_sFileName;
	}

protected:
	static const int split_tile_count    = 6;
	static const int split_texture_count = 6;
	static const int *split_texture_size[2];
	static const SplitRule split_rules[6];

protected:
	TSHORT                m_iSplitTileCount;    // 0x8
	TSHORT                m_iSplitTextureCount; // 0xA
	Tile                 *m_pTiles;             // 0xC
	Texture              *m_pTextures;          // 0x10
	Toshi::TCString       m_sFileName;          // 0x14
	Toshi::TSpriteShader *m_pShader;            // 0x18
};
