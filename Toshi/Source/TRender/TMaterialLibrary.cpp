#include "TMaterialLibrary.h"
#include "TRender/TRenderInterface.h"

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
}

TBOOL TMaterialLibrary::Create(TPCCHAR a_szFileName)
{
	TFile *f = TFile::Create(a_szFileName, 1);
	if (f) {
		if (ReadHeader(f)) {
			if (LoadTextures(f)) {

			}
		}
	}
	f->Destroy();
	TDPRINTF("Error loading material library %s\n");
	Destroy();
	return TFALSE;
}

void TMaterialLibrary::Destroy()
{
	m_iNumTextures = 0;
	delete m_pTextures;
	m_pTextures = TNULL;
}

TBOOL TMaterialLibrary::ReadHeader(TFile *file)
{
	Header header;
	TINT   read = file->Read(&header, sizeof(Header));
	if (read != sizeof(Header)) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error failed to read header\n");
		return TFALSE;
	}
	if (header.m_iMagic != MAKEFOURCC('T', 'M', 'L', '1')) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error incorrect magic number in header\n");
		return TFALSE;
	}
	if (header.m_iType != 0) {
		TDPRINTF("TMaterialLibrary::ReadHeader(): Error incorrect type number in header\n");
		return TFALSE;
	}
	return TTRUE;
}

// $TRenderInterface: FUNCTION 100100b0
TBOOL TMaterialLibrary::LoadTexture(TINT a_iIndex, TFile *file)
{
	TextureHeader dh;
	if (file->Read(&dh, sizeof(TextureHeader)) != sizeof(TextureHeader)) {
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
	TSystem::MemSet(m_pTextures, 0, sizeof(m_iNumTextures * 4));
	for (TINT i = 0; i < m_iNumTextures; i++) {
		if (!LoadTexture(i, file)) {
			return TFALSE;
		}
	}
	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000ff40
TMaterial *TMaterialLibrary::GetMaterial(TPCCHAR a_szMaterial)
{
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
	TMaterial *pSkin = reinterpret_cast<TMaterial *>(TRenderInterface::GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSKIN));
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
