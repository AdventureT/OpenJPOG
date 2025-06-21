#pragma once
#include "Defines.h"
#include "TShader.h"
#include "TKernel/TNodeList.h"
#include "TKernel/TFile.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

#define MAXTEXTURES 4

class TMaterialLibraryManager;

class TRENDERINTERFACE_EXPORTS TMaterialLibrary : public TNodeList<TMaterialLibrary>::TNode
{
	friend class TMaterialLibraryManager;

public:
	TMaterialLibrary(TMaterialLibraryManager *a_pManager);

private:


	struct TMLDISKHEADER
	{
		TINT m_iMagic;
		TINT m_iType;
	};

	typedef TCHAR MaterialName[32];

	struct TMLDISKMATERIALHEADER
	{
		TINT id;
		TSHORT flags;
		TSHORT numtextures;
	};

	enum TMLDISKMATERIALSHADERTYPE : short
	{
		TMLDISKMATERIALSHADERTYPE_SKIN         = 0x0000,
		TMLDISKMATERIALSHADERTYPE_TERRAIN      = 0x1000,
		TMLDISKMATERIALSHADERTYPE_TERRAINDECAL = 0x2000,
		TMLDISKMATERIALSHADERTYPE_SYSTEM       = 0x3000,
		TMLDISKMATERIALSHADERTYPE_SPRITE       = 0x4000,
		TMLDISKMATERIALSHADERTYPE_MASK         = 0xF000
	};
	
	struct TMLDISKTEXTUREHEADER
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
	TBOOL LoadSpriteMaterial(TINT a_iIndex, TFile *file, const TMLDISKMATERIALHEADER &dh);
	TBOOL LoadMaterial(TINT a_iIndex, TFile *file);
	TBOOL LoadMaterials(TFile *file);
	TBOOL ReadHeader(TFile *file);
	TBOOL LoadTexture(TINT a_iIndex, TFile *file);
	TBOOL LoadTextures(TFile *file);

	TINT              GetIndexForName(TPCCHAR a_szName, TPCHAR *a_pMaterialNames, TINT a_iMaterialCount);
	TMaterial *GetMaterial(TPCCHAR a_szMaterial);
	TTextureResource *GetTexture(TINT a_iIndex);

private:
	static const TTEXTURERESOURCEFORMAT gs_eRemapFormat[18];

	TMaterialLibraryManager *m_pManager;           // 0xC
	TINT                     m_iNumTextures;       // 0x10
	TTextureResource       **m_pTextures;          // 0x14
	TINT                     m_iNumMaterials;      // 0x18
	TPCHAR                  *m_pTextureNames;      // 0x1C
	TMaterial              **m_pMaterials;         // 0x20
	MaterialName            *m_pMaterialNames;     // 0x24
};

class TRENDERINTERFACE_EXPORTS TMaterialLibraryManager
{
	friend class TMaterialLibrary;

public:
	void Create();
	void Destroy();
	// $TRenderInterface: FUNCTION 1000b0d0
	TMaterial *GetInvalidMaterial()
	{
		return m_pInvalidMaterial;
	}
	TMaterial *GetMaterial(TPCCHAR a_szMaterial);

protected:

	TShader *GetShader(TINT a_iIndex)
	{
		return m_pShaders[a_iIndex];
	}

public:

	void SetShader(TINT a_iIndex, TShader *a_pShader)
	{
		m_pShaders[a_iIndex] = a_pShader;
	}

	TUINT LoadMaterialLibrary(TPCCHAR a_szFileName);
	void UnloadMaterialLibrary(TUINT a_iIndex);

private:
	TNodeList<TMaterialLibrary> m_oLibraries;       // 0x0
	TMaterial                  *m_pInvalidMaterial; // 0x10
	TShader                    *m_pShaders[5];      // 0x14
};

TOSHI_NAMESPACE_END
