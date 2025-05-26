#pragma once
#include "TKernel/TCString.h"
#include "TKernel/TLString.h"
#include "TKernel/TManagedPointer.h"
#include "AGUISystem.h"

class AGUIGameHUD
{
public:
	enum HUDComponents
	{

	};

	// $JPOG: FUNCTION 0046e4e0
	void AddToHUD(HUDComponents a_eHUDComponets)
	{
		SetHUD(static_cast<HUDComponents>(m_eHUDComponents | a_eHUDComponets));
	}
	// $JPOG: FUNCTION 0046e500
	void ToggleHUD(HUDComponents a_eHUDComponets)
	{
		SetHUD(static_cast<HUDComponents>(m_eHUDComponents ^ a_eHUDComponets));
	}
	// $JPOG: FUNCTION 00673140
	void SetHUD(HUDComponents a_eHUDComponets)
	{
		if (a_eHUDComponets == m_eHUDComponents) {
			return;
		}
		m_eHUDComponents = a_eHUDComponets;
		AGUISystem::GetGUISystem()->UpdateHUDComponets();
	}
	// $JPOG: FUNCTION 0046e4a0
	Toshi::TLString GetHintMessage()
	{
		return m_LSHintMessage;
	}
	// $JPOG: FUNCTION 0046e520
	HUDComponents GetHUD()
	{
		return m_eHUDComponents;
	}
	// $JPOG: FUNCTION 00673100
	void ClearBackgroundPicture()
	{
		m_szBKGMatLib = Toshi::TCString();
	}
	// $JPOG: FUNCTION 00673110
	void SetBackgroundMatLib(TPCCHAR a_szBKGMatLib)
	{
		m_szBKGMatLib = a_szBKGMatLib;
	}

private:
	Toshi::TLString m_LSHintMessage;  // 0x4
	HUDComponents   m_eHUDComponents; // 0x8
	Toshi::TCString m_szBKGMatLib;    // 0x2C
};
