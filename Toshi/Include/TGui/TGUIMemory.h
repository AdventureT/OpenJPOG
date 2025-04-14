#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPile.h"
#include "TGUIActionMap.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUIMemory
{
public:
	static TBOOL ms_bAllocUsePile;
	static TPile ms_oMemoryPile;
};

void *TOSHI_API TGUINew(TUINT a_uiSize);
void *TOSHI_API TGUIDelete(void *a_pMemory);
void TOSHI_API  TGUISetUseMemoryPile(TBOOL a_bEnable);

TOSHI_NAMESPACE_END
