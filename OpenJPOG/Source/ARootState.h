#pragma once
#include "TKernel/TObject.h"
#include "AGUIGameHUD.h"

class ARootState : public Toshi::TObject
{
	DECLARE_DYNAMIC(ARootState)


public:

	AGUIGameHUD& GetHUDState() { return m_oHUDState; }

private:
	ARootState* m_pParent;   // 0x4
	ARootState* m_pNext;     // 0x8
	AGUIGameHUD m_oHUDState; // 0x10
};

