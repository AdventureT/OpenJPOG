#pragma once
#include "Toshi/Defines.h"
#include "PPropertyParser/PProperties.h"

class AOptionsLogic
{
public:
	enum OPTION
	{
		OPTION_SCREENRES
	};

	struct AOptionSetting
	{
		OPTION m_eOption;
		TBOOL m_bFetched;
	};

	struct AScreenRes
	{
		TINT m_iScreenWidth;
		TINT m_iScreenHeight;
		TINT m_iScreenDepth;
		TINT m_iScreenUnk;
	};
public:
	AOptionsLogic();

	TBOOL GetOption(OPTION a_eOption, AScreenRes &a_rScreenRes);
	TBOOL SetOption(OPTION a_eOption, AScreenRes &a_rScreenRes);
	void OptionGet(AOptionSetting &a_rSetting);

private:
	static AScreenRes m_oScreenRes;
};

class AOptions
{
public:
	AOptions();

	enum Result
	{
		RESULT_OK = 0,
		RESULT_ERROR = 3
	};

	TBOOL GetOption(TPCCHAR a_szProp, TINT &a_iValue);

	Result LoadOptions();
	Result LoadOptions(TINT a_int, TINT a_int2, const Toshi::TCString &a_szOptionsDir, const Toshi::TCString &a_szOptionsName);

	TINT GetAutoSaveState() const
	{
		return m_iAutoSaveState;
	}

private:
	static TPCCHAR sm_szOptionsName;
	static TPCCHAR sm_szOptionsDir;
	static const TINT sm_iSlot = -1;
	static const TINT sm_iPort = -1;

	static AOptions *ms_pSingleton;

	TINT m_iAutoSaveState;    // 0x1C
	PProperties *m_pUnkProps; // 0x20
	PProperties *m_pCurProps; // 0x24
};

