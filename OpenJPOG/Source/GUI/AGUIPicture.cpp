#include "AGUIPicture.h"
#include "AGUISystem.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(AGUIPicture, TObject)

const AGUIPicture::SplitRule AGUIPicture::split_rules[6] = {
	SplitRule{ TVector2(0.0f, 256.0f), TVector2(0.0f, 256.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 1.0f), 0, 0, 0 },
	SplitRule{ TVector2(255.0f, 511.0f), TVector2(0.0f, 256.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 1.0f), 1, 0, 0 },
	SplitRule{ TVector2(510.0f, 638.0f), TVector2(0.0f, 256.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 1.0f), 2, 0, 0 },
	SplitRule{ TVector2(0.0f, 256.0f), TVector2(255.0f, 447.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 0.75f), 3, 0, 0 },
	SplitRule{ TVector2(255.0f, 511.0f), TVector2(255.0f, 447.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 0.75f), 4, 0, 0 },
	SplitRule{ TVector2(510.0f, 638.0f), TVector2(255.0f, 447.0f), TVector2(0.0f, 1.0f), TVector2(0.0f, 0.75f), 5, 0, 0 }
};

AGUIPicture::AGUIPicture()
{
	m_iSplitTileCount    = 0;
	m_iSplitTextureCount = 0;
	m_pTiles             = TNULL;
	m_pTextures          = TNULL;
	m_pShader            = TNULL;
}

void AGUIPicture::Delete()
{
	Flush();
	delete this;
}

void AGUIPicture::Create(TPCCHAR a_szFileName, Toshi::TSpriteShader *a_pShader)
{
	m_sFileName = a_szFileName;
	m_pShader = a_pShader;
	Cache();
}

void AGUIPicture::Render()
{
	AGUISystem *system = AGUISystem::GetGUISystem();
	TFLOAT height = system->GetScreen()->GetHeight() / 447.0f;
	TFLOAT width = system->GetScreen()->GetWidth() / 638.0f;
	for (TUINT i = 0; i < m_iSplitTileCount; i++) {
		m_pShader->SetColour(TGUIColour());
		m_pShader->SetMaterial(*m_pTiles[i].ppMaterial);
	}
}
