#pragma once
#include "Toshi/Defines.h"
#include "PPropertyParser/PProperties.h"

class AOptions
{
public:
	enum Result
	{

	};

	TINT GetAutoSaveState() const
	{
		return m_iAutoSaveState;
	}

private:
	static TPCCHAR sm_szOptionsName;
	static TPCCHAR sm_szOptionsDir;
	static const TINT sm_iSlot = -1;
	static const TINT sm_iPort = -1;

	TINT m_iAutoSaveState;           // 0x1C
	PProperty *m_pCurProps; // 0x24
};

