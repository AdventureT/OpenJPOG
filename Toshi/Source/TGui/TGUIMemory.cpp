#include "TGUIMemory.h"
#include "TKernel/TMemory.h"

TOSHI_NAMESPACE_BEGIN

TBOOL TGUIMemory::ms_bAllocUsePile = TTRUE;
TPile TGUIMemory::ms_oMemoryPile = TPile(0x8000, 0x100000, 0);

void* TOSHI_API TGUINew(TUINT a_uiSize)
{
	if (TGUIMemory::ms_bAllocUsePile) {
	}
	return tmalloc(a_uiSize, TNULL, -1);
}

void* TOSHI_API TGUIDelete(void* a_pMemory)
{
	return TNULL;
}

void TOSHI_API TGUISetUseMemoryPile(TBOOL a_bEnable)
{
	TGUIMemory::ms_bAllocUsePile = a_bEnable;
}

TOSHI_NAMESPACE_END