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

	// $JPOG: 0046e4e0 FUNCTION
	void AddToHUD(HUDComponents a_eHUDComponets)
	{
		SetHUD(static_cast<HUDComponents>(m_eHUDComponents | a_eHUDComponets));
	}
	// $JPOG: 0046e500 FUNCTION
	void ToggleHUD(HUDComponents a_eHUDComponets)
	{
		SetHUD(static_cast<HUDComponents>(m_eHUDComponents ^ a_eHUDComponets));
	}
	// $JPOG: 00673140 FUNCTION
	void SetHUD(HUDComponents a_eHUDComponets)
	{
		if (a_eHUDComponets == m_eHUDComponents) {
			return;
		}
		m_eHUDComponents = a_eHUDComponets;
		AGUISystem::GetGUISystem()->UpdateHUDComponets();
	}
	// $JPOG: 0046e4a0 FUNCTION
	Toshi::TLString GetHintMessage()
	{
		return m_LSHintMessage;
	}
	// $JPOG: 0046e520 FUNCTION
	HUDComponents GetHUD()
	{
		return m_eHUDComponents;
	}
	// $JPOG: 00673100 FUNCTION
	void ClearBackgroundPicture()
	{
		m_szBKGMatLib = Toshi::TCString();
	}
	// $JPOG: 00673110 FUNCTION
	void SetBackgroundMatLib(TPCCHAR a_szBKGMatLib)
	{
		m_szBKGMatLib = a_szBKGMatLib;
	}

private:
	Toshi::TLString m_LSHintMessage;  // 0x4
	HUDComponents   m_eHUDComponents; // 0x8
	Toshi::TCString m_szBKGMatLib;    // 0x2C
};
