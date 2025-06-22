#include "AGUIMatLibPicture.h"
#include "TRender/TRenderInterface.h"
#include "AOptions.h"
#include "main.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(AGUIMatLibPicture, AGUIPicture)

AGUIMatLibPicture::AGUIMatLibPicture()
{
	m_tmlidx = -1;
}

void AGUIMatLibPicture::LoadMaterialLibrary()
{
	TCString sixteen = TCString("16");
	TINT          screendepth = 32;
	AOptionsLogic::LMH lmh;
	AOptionsLogic options;
	g_oTheApp.GetRootTask()->GetOptions()->GetOption("ScreenDepth", screendepth);
	options.GetOption(AOptionsLogic::OPTION_SCREENDEPTH, lmh);
	TBOOL supportscreendepth = TTRUE;
	if (screendepth != 16) {
		supportscreendepth = TRenderInterface::GetRenderer()->Supports32BitTextures();
		if (supportscreendepth) {
			supportscreendepth = lmh != AOptionsLogic::LMH_UNK3;
		}
	}
	// Should not be here!
	supportscreendepth = TFALSE;
	if (supportscreendepth) {
		TINT extensionidx = m_sFileName.FindReverse('.');
		TINT     len      = m_sFileName.Length();
		TCString fullname = m_sFileName.Mid(0, extensionidx) + sixteen + m_sFileName.Mid(extensionidx, len);
		m_tmlidx          = TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->LoadMaterialLibrary(fullname);
	}
	else if (m_tmlidx == -1) {
		m_tmlidx = TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->LoadMaterialLibrary(m_sFileName);
	}
}

void AGUIMatLibPicture::UnloadMaterialLibrary()
{
	TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->UnloadMaterialLibrary(m_tmlidx);
	m_tmlidx = -1;
}

void AGUIMatLibPicture::SetFile(TPCCHAR a_szFile)
{
	if (m_sFileName != a_szFile) {
		Flush();
	}
	m_sFileName = a_szFile;
	if (!m_sFileName.IsEmpty()) {
		TINT fileNameIndex = m_sFileName.FindReverse('/');
		TINT extensionidx  = m_sFileName.FindReverse('.');
		m_sPrefix          = m_sFileName.Mid(fileNameIndex+1, extensionidx);
	}
}

void AGUIMatLibPicture::Create(TSpriteShader *a_pShader)
{
	m_pShader = a_pShader;
}

void AGUIMatLibPicture::Flush()
{
	if (m_iSplitTileCount == 0) {
		return;
	}
	delete m_pTextures;
	m_pTextures = TNULL;
	m_iSplitTextureCount = 0;
	delete m_pTiles;
	m_pTiles = TNULL;
	m_iSplitTileCount = 0;

}

void AGUIMatLibPicture::Cache()
{
	if (m_iSplitTileCount != 0) {
		return;
	}
	if (!m_sFileName.GetString()) {
		return;
	}
	m_iSplitTileCount    = split_tile_count;
	m_pTiles             = new Tile[m_iSplitTileCount];
	m_iSplitTextureCount = split_texture_count;
	m_pTextures          = new Texture[m_iSplitTextureCount];
	LoadMaterialLibrary();
	TCString format;
	for (TINT i = 0; i < m_iSplitTextureCount; i++) {
		Toshi::TMaterial *pMat = Toshi::TRenderInterface::GetRenderer()->GetMaterialLibraryManager()->GetMaterial(format.Format("%s_%d", m_sPrefix, i));
		m_pTextures[i].pMaterial = static_cast<TSpriteMaterial *>(pMat);
		m_pTextures[i].pTexture  = TNULL;
	}
	for (TINT i = 0; i < m_iSplitTileCount; i++) {
		m_pTiles[i].ppMaterial = &m_pTextures[split_rules[i].index].pMaterial;
		m_pTiles[i].pos1       = split_rules[i].pos1;
		m_pTiles[i].pos2       = split_rules[i].pos2;
		m_pTiles[i].uv1        = split_rules[i].uv1;
		m_pTiles[i].uv2        = split_rules[i].uv2;
	}
}
