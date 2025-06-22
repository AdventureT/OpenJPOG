#include "TMaterialLibrary.h"
#include "TRender/TRenderInterface.h"
#include "TKernel/TMemory.h"
#include "TSpriteShader/Include/TSpriteShader.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

const TTEXTURERESOURCEFORMAT TMaterialLibrary::gs_eRemapFormat[18] = {
	TTEXTURERESOURCEFORMAT_R8G8B8A8,
	TTEXTURERESOURCEFORMAT_R8G8B8,
	TTEXTURERESOURCEFORMAT_R5G5B5A1,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_DDS,
	TTEXTURERESOURCEFORMAT_R4G4B4A4,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_UNKNOWN4,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
	TTEXTURERESOURCEFORMAT_INVALID,
};

TMaterialLibrary::TMaterialLibrary(TMaterialLibraryManager *a_pManager)
{
	m_pManager = a_pManager;
	m_iNumTextures = 0;
	m_pTextures    = TNULL;
	m_iNumMaterials = 0;
	m_pTextureNames  = TNULL;
	m_pMaterials     = TNULL;
	m_pMaterialNames = TNULL;
}

TBOOL TMaterialLibrary::Create(TPCCHAR a_szFileName)
{
	TFile *f = TFile::Create(a_szFileName, 1);
	if (f) {
		if (ReadHeader(f)) {
			if (LoadTextures(f)) {
				if (LoadMaterials(f)) {
					f->Destroy();
					return TTRUE;
				}
			}
		}
	}
	f->Destroy();
	TDPRINTF("Error loading material library %s\n", a_szFileName);
	Destroy();
	return TFALSE;
}

void TMaterialLibrary::Destroy()
{
	m_iNumTextures = 0;
	delete m_pTextures;
	m_pTextures = TNULL;
}

TBOOL TMaterialLibrary::LoadSpriteMaterial(TINT a_iIndex, TFile *file, const TMLDISKMATERIALHEADER &dh)
{
	TSpriteShader *pShader = static_cast<TSpriteShader *>(m_pManager->GetShader(4));
	TVALIDADDRESS(pShader);
	TSpriteMaterial *pMat = pShader->CreateMaterial(TNULL);
	if (!pMat) {
		TDPRINTF("TMaterialLibrary::LoadSpriteMaterial(): CreateMaterial() failed for %d\n", a_iIndex);
		return TFALSE;
	}
	TASSERT(dh.numtextures <= 4);
	for (TINT i = 0; i < dh.numtextures; i++) {
		TINT textureID;
		if (file->Read(&textureID, 4) != 4) {
			TDPRINTF("TMaterialLibrary::LoadSpriteMaterial(): Failed to read texture id %d for material %d\n", i, a_iIndex);
			return TFALSE;
		}
		pMat->SetTexture1(GetTexture(a_iIndex));
		m_pTextures[i]->SetAddressModeMode(TTextureResource::ADDRESSMODE_CLAMP);
	}
	if ((dh.flags & 4) != 0) {
		pMat->SetBlendMode(1);
	}
	else if ((dh.flags & 8) != 0) {
		pMat->SetBlendMode(4);
	}
	else if ((dh.flags & 0x10) != 0) {
		pMat->SetBlendMode(3);
	}
	else {
		pMat->SetBlendMode(0);
	}
	return TTRUE;
}

TBOOL TMaterialLibrary::LoadMaterial(TINT a_iIndex, TFile *file)
{
	TMLDISKMATERIALHEADER dh;
	TINT read = file->Read(&dh, sizeof(TMLDISKMATERIALHEADER));
	if (read != sizeof(TMLDISKMATERIALHEADER)) {
		TDPRINTF("TMaterialLibrary::LoadMaterial(): Failed to read material header\n");
		return TFALSE;
	}
	TDPRINTF("Loading material \"%s\" (id %d)\n", m_pMaterialNames[a_iIndex], dh.id);
	TMLDISKMATERIALSHADERTYPE eShaderType = (TMLDISKMATERIALSHADERTYPE)(dh.flags & TMLDISKMATERIALSHADERTYPE_MASK);
	switch (eShaderType)
	{
		case Toshi::TMaterialLibrary::TMLDISKMATERIALSHADERTYPE_SKIN:
			TDPRINTF("Not implemented");
			break;
		case Toshi::TMaterialLibrary::TMLDISKMATERIALSHADERTYPE_TERRAIN:
			TDPRINTF("Not implemented");
			break;
		case Toshi::TMaterialLibrary::TMLDISKMATERIALSHADERTYPE_TERRAINDECAL:
			TDPRINTF("Not implemented");
			break;
		case Toshi::TMaterialLibrary::TMLDISKMATERIALSHADERTYPE_SYSTEM:
			TDPRINTF("Not implemented");
			break;
		case Toshi::TMaterialLibrary::TMLDISKMATERIALSHADERTYPE_SPRITE:
			return LoadSpriteMaterial(a_iIndex, file, dh);
		default:
			TASSERT(!"************* TMaterialLibrary::LoadMaterial(): Unrecognised shader type");
	}
	return TFALSE;
}

TBOOL TMaterialLibrary::LoadMaterials(TFile *file)
{
	if (file->Read(&m_iNumMaterials, 4) != 4) {
		TDPRINTF("TMaterialLibrary::LoadMaterials(): Failed to read number of materials\n");
		return TFALSE;
	}
	m_pTextureNames = new TCHAR *[m_iNumMaterials];
	m_pMaterialNames = new MaterialName[m_iNumMaterials];
	if (file->Read(m_pMaterialNames, m_iNumMaterials * sizeof(MaterialName)) != m_iNumMaterials * sizeof(MaterialName)) {
		TDPRINTF("TMaterialLibrary::LoadMaterials(): Failed to read number of materials\n");
		return TFALSE;
	}
	m_pMaterials = new TMaterial *[m_iNumMaterials];
	for (TINT i = 0; i < m_iNumMaterials; i++) {
		m_pMaterials[i]    = TNULL;
		m_pTextureNames[i] = m_pMaterialNames[i];
	}
	for (TINT i = 0; i < m_iNumMaterials; i++) {
		TMaterialLibraryManager *pManager = TRenderInterface::GetRenderer()->GetMaterialLibraryManager();
		for (auto it = pManager->m_oLibraries.Begin(); it != pManager->m_oLibraries.End(); it++) {
			TMaterial *pMat = it->GetMaterial(m_pMaterialNames[i]);
			if (pMat) {
				TDPRINTF("******** TMaterialLibraryManager::LoadMaterials() MATERIAL \"%s\" ALREADY LOADED BY ANOTHER LIBRARY!!!!!!! **********\n", m_pMaterialNames[i]);
			}
		}
		if (!LoadMaterial(i, file)) {
			return TFALSE;
		}
	}
	return TTRUE;
}

TBOOL TMaterialLibrary::ReadHeader(TFile *file)
{
	TMLDISKHEADER dh;
	TINT          read = file->Read(&dh, sizeof(TMLDISKHEADER));
	if (read != sizeof(TMLDISKHEADER)) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error failed to read header\n");
		return TFALSE;
	}
	if (dh.m_iMagic != MAKEFOURCC('T', 'M', 'L', '1')) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error incorrect magic number in header\n");
		return TFALSE;
	}
	if (dh.m_iType != 0) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error incorrect type number in header\n");
		return TFALSE;
	}
	return TTRUE;
}

// $TRenderInterface: FUNCTION 100100b0
TBOOL TMaterialLibrary::LoadTexture(TINT a_iIndex, TFile *file)
{
	TMLDISKTEXTUREHEADER dh;
	if (file->Read(&dh, sizeof(TMLDISKTEXTUREHEADER)) != sizeof(TMLDISKTEXTUREHEADER)) {
		TDPRINTF("TMaterialLibrary::LoadTexture(): Failed to read texture header %d\n");
		return TFALSE;
	}
	TASSERT(dh.id < m_iNumTextures);
	TTextureFactory *factory = static_cast<TTextureFactory *>(TRenderInterface::GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_TEXTUREFACTORY));
	TPCHAR pMem = new TCHAR[dh.texturesize];
	TVALIDADDRESS(pMem);
	if (!pMem) {
		delete pMem;
		return TTRUE;
	}
	if (file->Read(pMem, dh.texturesize) != dh.texturesize) {
		delete pMem;
		return TFALSE;
	}
	TTEXTURERESOURCEFORMAT eFormat = gs_eRemapFormat[dh.format];
	TASSERT(eFormat != TTEXTURERESOURCEFORMAT_INVALID);
	TTextureResource *res = factory->CreateEx(pMem, dh.texturesize, dh.width, dh.height, 0, eFormat, (dh.flags & 2) == 0);
	if (!res) {
		delete pMem;
		return TTRUE;
	}
	m_pTextures[dh.id] = res;
}

// $TRenderInterface: FUNCTION 1000fff0
TBOOL TMaterialLibrary::LoadTextures(TFile *file)
{
	if (file->Read(&m_iNumTextures, 4) != 4) {
		TDPRINTF("TMaterialLibrary::LoadTextures(): Failed to read numtextures\n");
		return TFALSE;
	}
	m_pTextures = new TTextureResource *[m_iNumTextures];
	TSystem::MemSet(m_pTextures, 0, m_iNumTextures * 4);
	for (TINT i = 0; i < m_iNumTextures; i++) {
		if (!LoadTexture(i, file)) {
			return TFALSE;
		}
	}
	return TTRUE;
}

// $TRenderInterface: FUNCTION 10010f60
TINT TMaterialLibrary::GetIndexForName(TPCCHAR a_szName, TPCHAR *a_pMaterialNames, TINT a_iNumMaterials)
{
	for (TINT low = 0; low < a_iNumMaterials;) {
		if (a_iNumMaterials == low + 1) {
			if (TSystem::StringCompareNoCase(a_szName, a_pMaterialNames[low], 0x20) != 0) {
				break;
			}
			return low;
		}
		TINT mid = (a_iNumMaterials - low) / 2 + low;
		TINT cmpResult = TSystem::StringCompareNoCase(a_szName, a_pMaterialNames[mid], 0x20);
		if (cmpResult < 0) {
			a_iNumMaterials = mid;
		}
		else if (cmpResult == 0) {
			return mid;
		}
		else {
			low = mid;
		}
	}
	return -1;
}

// $TRenderInterface: FUNCTION 1000ff40
TMaterial *TMaterialLibrary::GetMaterial(TPCCHAR a_szMaterial)
{
	TINT iIndex = GetIndexForName(a_szMaterial, m_pTextureNames, m_iNumMaterials);
	if (iIndex >= 0 && iIndex < m_iNumMaterials) {
		return m_pMaterials[iIndex];
	}
	return TNULL;
}

TTextureResource *TMaterialLibrary::GetTexture(TINT a_iIndex)
{
	TASSERT(a_iIndex < (TINT)m_iNumTextures);
	return m_pTextures[a_iIndex];
}

// $TRenderInterface: FUNCTION 10011020
void TMaterialLibraryManager::Create()
{
	//TMaterial *pSkin = reinterpret_cast<TMaterial *>(TRenderInterface::GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSKIN));

}

// $TRenderInterface: FUNCTION 100110a0
void TMaterialLibraryManager::Destroy()
{
	TASSERT(m_oLibraries.IsEmpty());
	if (m_pInvalidMaterial) {
		m_pInvalidMaterial->PostRender();
		m_pInvalidMaterial = TNULL;
	}
}

// $TRenderInterface: FUNCTION 10011290
TMaterial *TMaterialLibraryManager::GetMaterial(TPCCHAR a_szMaterial)
{
	if (m_oLibraries.IsEmpty()) {
		TDPRINTF("******** TMaterialLibraryManager::GetMaterial(%s) FAILED!!!!!!! **********\n", a_szMaterial);
		return m_pInvalidMaterial;
	}
	for (auto it = m_oLibraries.Begin(); it != m_oLibraries.End(); it++) {
		TMaterial *pMat = it->GetMaterial(a_szMaterial);
		if (pMat) {
			return pMat;
		}
	}
	return TNULL;
}

TUINT TMaterialLibraryManager::LoadMaterialLibrary(TPCCHAR a_szFileName)
{
	TMaterialLibrary *lib = new TMaterialLibrary(this);
	if (!lib->Create(a_szFileName)) {
		delete lib;
		return -1;
	}
	m_oLibraries.InsertTail(*lib);
	return 0;
}

void TMaterialLibraryManager::UnloadMaterialLibrary(TUINT a_iIndex)
{
}

TOSHI_NAMESPACE_END
