#pragma once

#include "TKernel/TCString.h"
#include "TKernel/TLString.h"
#include "TKernel/TManagedPointer.h"

class AGUIGameHUD
{
public:

	enum HUDComponents
	{

	};

	Toshi::TLString GetHintMessage()
	{
		return *m_LSHintMessage.m_pObject;
	}

	HUDComponents GetHUD()
	{
		return m_eHUDComponents;
	}

	void SetBackgroundMatLib(TPCCHAR a_szBKGMatLib)
	{
		m_szBKGMatLib = a_szBKGMatLib;
	}

private:
	Toshi::TManagedPtr<Toshi::TLString> m_LSHintMessage; // 0x4
	HUDComponents m_eHUDComponents;                      // 0x8
	Toshi::TCString m_szBKGMatLib;                       // 0x2C
};

