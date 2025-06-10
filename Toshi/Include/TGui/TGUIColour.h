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
private:
	TCHAR m_alpha; // 0x0
	TCHAR m_red;   // 0x1
	TCHAR m_green; // 0x2
	TCHAR m_blue;  // 0x3
};

TOSHI_NAMESPACE_END
