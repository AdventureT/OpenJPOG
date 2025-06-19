#pragma once
#include "Defines.h"
#include "TKernel/TNodeList.h"
#include "TGUIDeserialisable.h"

TOSHI_NAMESPACE_BEGIN

class TGUIScreen;

#define STATE_ENABLED  0x01
#define STATE_FOCUSED  0x02
#define STATE_VISIBLE  0x04
#define STATE_ROLLOVER 0x08
#define STATE_SELECTED 0x10
#define STATE_ONSCREEN (STATE_ENABLED | STATE_VISIBLE)

class TGUIINTERFACE_EXPORTS TGUIWidget : public TGUIDeserialisable
	, public TNodeList<TGUIWidget>::TNode
{
	DECLARE_DYNAMIC(TGUIWidget)

public:

	TGUIWidget();

	// $TGUIInterface: FUNCTION 1001dd80
	void SetSize(TINT a_iWidth, TINT a_iHeight)
	{
		if (!m_iSizeModeHoriz && !m_iSizeModeVert) {
			return;
		}
		if (m_iWidth != a_iWidth || m_iHeight != a_iHeight) {
			m_bIsEnabled = TFALSE;
		}
		m_iWidth = a_iWidth;
		m_iHeight = a_iHeight;
	}
	void InvalidateComponentCache(TBOOL a_bRecursive);
	void SetState(TUINT a_iState, TUINT a_iState2);
	// $TGUIInterface: FUNCTION 1001e630
	TBOOL CanFocus()
	{
		for (TGUIWidget *widget = this; widget; widget = widget->m_pParentWidget) {
			if (!widget->IsState(STATE_ENABLED) || !widget->IsState(STATE_VISIBLE)) {
				return TFALSE;
			}
		}
		return TTRUE;
	}
	TGUIScreen *GetScreen();
	// $TGUIInterface: FUNCTION 100076c0
	TINT GetWidth() const
	{
		return m_iWidth;
	}
	// $TGUIInterface: FUNCTION 100076b0
	TINT GetHeight() const
	{
		return m_iHeight;
	}
	// $TGUIInterface: FUNCTION 10007550
	TBOOL IsState(TUINT a_iStateMask, TUINT a_iExpectedState) const
	{
		return (m_iState & a_iStateMask) == a_iExpectedState;
	}
	// $TGUIInterface: FUNCTION 10007570
	TBOOL IsState(TUINT a_iStateMask) const
	{
		return (m_iState & a_iStateMask) != 0;
	}


private:
	TGUIWidget *m_pParentWidget;  // 0x44
	TSHORT      m_iWidth;         // 0x70
	TSHORT      m_iHeight;        // 0x72
	TINT        m_iSizeModeHoriz; // 0x74
	TINT        m_iSizeModeVert;  // 0x78
	TBOOL       m_bIsEnabled;     // 0x84
	TUINT       m_iState;         // 0x88
};

TOSHI_NAMESPACE_END
