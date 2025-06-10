#pragma once
#include "Defines.h"
#include "TShader.h"
#include "TKernel/TNodeList.h"
#include "TKernel/TFile.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class TMaterialLibraryManager;

class TRENDERINTERFACE_EXPORTS TMaterialLibrary : public TNodeList<TMaterialLibrary>::TNode
{
	friend class TMaterialLibraryManager;

public:
	TMaterialLibrary(TMaterialLibraryManager *a_pManager);

private:

	struct Header
	{
		TINT m_iMagic;
		TINT m_iType;
	};
	
	struct TextureHeader
	{
		TINT    id;
		TINT    texturesize;
		TUSHORT flags;
		TSHORT  unk;
		TINT    unk2;
		TUSHORT format;
		TUSHORT width;
		TUSHORT height;
		TUSHORT unk3;
		TINT    unk4;
	};

protected:

	TBOOL Create(TPCCHAR a_szFileName);
	void  Destroy();
	TBOOL ReadHeader(TFile *file);
	TBOOL LoadTexture(TINT a_iIndex, TFile *file);
	TBOOL LoadTextures(TFile *file);

	TMaterial *GetMaterial(TPCCHAR a_szMaterial);
	TTextureResource *GetTexture(TINT a_iIndex);

private:
	static const TTEXTURERESOURCEFORMAT gs_eRemapFormat[18];

	TMaterialLibraryManager *m_pManager;     // 0xC
	TINT                     m_iNumTextures; // 0x10
	TTextureResource       **m_pTextures;    // 0x14
};

class TRENDERINTERFACE_EXPORTS TMaterialLibraryManager
{
public:
	void Create();
	void Destroy();
	// $TRenderInterface: FUNCTION 1000b0d0
	TMaterial *GetInvalidMaterial()
	{
		return m_pInvalidMaterial;
	}
	TMaterial *GetMaterial(TPCCHAR a_szMaterial);

	TUINT LoadMaterialLibrary(TPCCHAR a_szFileName);
	void UnloadMaterialLibrary(TUINT a_iIndex);

private:
	TNodeList<TMaterialLibrary> m_oLibraries;       // 0x0
	TMaterial                  *m_pInvalidMaterial; // 0x10
};

TOSHI_NAMESPACE_END
