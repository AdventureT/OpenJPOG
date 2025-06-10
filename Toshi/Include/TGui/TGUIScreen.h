#pragma once
#include "TGuiWidget.h"
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

	TEmitter<TGUIScreen, TGUIScreenPaintEvent> *GetPaintEmitter()
	{
		return &m_oPaintEmitter;
	}

private:
	TEmitter<TGUIScreen, TGUIScreenPaintEvent> m_oPaintEmitter;
};

TOSHI_NAMESPACE_END
