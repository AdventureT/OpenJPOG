#pragma once
#include "Toshi/Defines.h"
#include "PPropertyParser/PProperties.h"

class AOptions
{
public:
	enum Result
	{
		RESULT_OK = 0,
		RESULT_ERROR = 3
	};

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

	TINT m_iAutoSaveState;    // 0x1C
	PProperties *m_pUnkProps; // 0x20
	PProperties *m_pCurProps; // 0x24
};

