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

	friend class PGUITRViewportHandler;

public:
	TGUIScreen();

	void NotifyDescendantCantFocus(TGUIWidget *a_pWidget);
	void NotifyDescendantCanFocus(TGUIWidget *a_pWidget);

protected:

	void Paint(TGUIWidget *a_pWidget);

public:

	void SetDisplayContext(TGUIDisplayContext *a_pDisplayContext)
	{
		m_pDisplayContext = a_pDisplayContext;
	}

	TGUIDisplayContext *GetDisplayContext() const
	{
		return m_pDisplayContext;
	}

	TEmitter<TGUIScreen, TGUIScreenPaintEvent> *GetPaintEmitter()
	{
		return &m_oPaintEmitter;
	}

	TBOOL IsPaintContinued()
	{
		return m_pLastPaintedWidget;
	}

private:
	TEmitter<TGUIScreen, TGUIScreenPaintEvent> m_oPaintEmitter;   // 0xB4
	TGUIDisplayContext                        *m_pDisplayContext; // 0xC0
	TGUIWidget                                *m_pLastPaintedWidget; // 0x134
};

TOSHI_NAMESPACE_END
