#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIColour
{
public:
	// $TGUIInterface: FUNCTION 10008c30
	TGUIColour()
	{
		m_alpha = -1;
		m_red   = -1;
		m_green = -1;
		m_blue  = -1;
	}
	// $TGUIInterface: FUNCTION 10008c10
	TGUIColour(TBYTE a_alpha, TBYTE a_red, TBYTE a_green, TBYTE a_blue)
	{
		m_alpha = a_alpha;
		m_red   = a_red;
		m_green = a_green;
		m_blue  = a_blue;
	}
	// $TGUIInterface: FUNCTION 100089e0
	TUINT GetABGR() const
	{
		return m_alpha << 0x18 | m_blue << 0x10 | m_green << 0x8 | m_red;
	}
	// $TGUIInterface: FUNCTION 10008a00
	TUINT GetARGB() const
	{
		return m_alpha << 0x18 | m_red << 0x10 | m_green << 0x8 | m_blue;
	}

private:
	TBYTE m_alpha; // 0x0
	TBYTE m_red;   // 0x1
	TBYTE m_green; // 0x2
	TBYTE m_blue;  // 0x3
};

TOSHI_NAMESPACE_END
