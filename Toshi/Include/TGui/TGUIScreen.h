#pragma once
#include "TGuiWidget.h"
#include "TGUIDisplayContext.h"
#include "TKernel/TEvent.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIScreenPaintEvent
{
};

class TGUIINTERFACE_EXPORTS TGUIScreen : public TGUIWidget
{
	DECLARE_DYNAMIC(TGUIScreen)

public:
	TGUIScreen();

	void NotifyDescendantCantFocus(TGUIWidget *a_pWidget);
	void NotifyDescendantCanFocus(TGUIWidget *a_pWidget);

	void SetDisplayContext(TGUIDisplayContext *a_pDisplayContext)
	{
		m_pDisplayContext = a_pDisplayContext;
	}

	TEmitter<TGUIScreen, TGUIScreenPaintEvent> *GetPaintEmitter()
	{
		return &m_oPaintEmitter;
	}

private:
	TEmitter<TGUIScreen, TGUIScreenPaintEvent> m_oPaintEmitter;
	TGUIDisplayContext                        *m_pDisplayContext; // 0xC0
};

TOSHI_NAMESPACE_END
