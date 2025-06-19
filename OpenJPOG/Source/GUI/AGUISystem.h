#pragma once
#include "TKernel/TCString.h"
#include "TKernel/TTask.h"
#include "TKernel/TManagedPointer.h"
#include "TKernel/TEvent.h"
#include "TRender/TNullResource.h"
#include "TGui/TGUIInterface.h"
#include "TGUI/TGUIScreen.h"
#include "PGuiRenderer/PGUITRDisplayContext.h"
#include "TSpriteShader/Include/TSpriteShader.h"
#include "AGUIMatLibPicture.h"
#include "AGUITextureFactory.h"

class AGUISystem : public Toshi::TTask
{
	DECLARE_DYNAMIC(AGUISystem)
public:
	AGUISystem();

	virtual TBOOL OnCreate() override;
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) override;

public:


	void                                     UpdateHUDComponets();
	// $JPOG: FUNCTION 0067e5e0
	Toshi::TManagedPtr<Toshi::TGUIInterface> GetGUIInterface() const
	{
		return m_pGUIInterface;
	}
	// $JPOG: FUNCTION 0046e340
	Toshi::TGUIScreen *GetScreen() const
	{
		return m_pScreen;
	}
	// $JPOG: FUNCTION 0046e3a0
	Toshi::TSpriteShader *GetShader()
	{
		return m_pSpriteShader;
	}

	static AGUISystem *TOSHI_API GetGUISystem();

protected:
	static TBOOL OnScreenPaint(AGUISystem *a_pGUISystem, Toshi::TGUIScreen *a_pScreen, Toshi::TGUIScreenPaintEvent *a_pEvent);

private:
	Toshi::TManagedPtr<Toshi::TGUIInterface>                                     m_pGUIInterface;        // 0x24
	Toshi::TGUIScreen                                                           *m_pScreen;              // 0x28
	PGUITRDisplayContext                                                        *m_pDisplayContext;      // 0xA4
	AGUITextureFactory                                                          *m_pTextureFactory;      // 0xA8
	PGUITRFontFactory                                                           *m_pFontFactory;         // 0xAC
	Toshi::TListener<Toshi::TGUIScreen, Toshi::TGUIScreenPaintEvent, AGUISystem> m_oScreenPaintListener; // 0x118
	Toshi::TNullResource                                                        *m_pNullResource;        // 0x140
	Toshi::TSpriteShader                                                        *m_pSpriteShader;        // 0x144
	Toshi::TScene                                                               *m_pScenes[2];           // 0x190
	AGUIMatLibPicture                                                           *m_pMatLibPic;           // 0x19C
};
