#include "TGUIMemory.h"
#include "TKernel/TMemory.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

TBOOL TGUIMemory::ms_bAllocUsePile = TTRUE;
TPile TGUIMemory::ms_oMemoryPile   = TPile(0x8000, 0x100000, 0);

void *TOSHI_API TGUINew(TUINT a_uiSize)
{
	if (TGUIMemory::ms_bAllocUsePile) {
		return TGUIMemory::ms_oMemoryPile.RawAlloc(a_uiSize, 4);
	}
	return tmalloc(a_uiSize);
}

void TOSHI_API TGUIDelete(void *a_pMemory)
{
	if (!TGUIMemory::ms_oMemoryPile.RawIsInside(a_pMemory)) {
		tfree(a_pMemory);
	}
}

void TOSHI_API TGUISetUseMemoryPile(TBOOL a_bEnable)
{
	TGUIMemory::ms_bAllocUsePile = a_bEnable;
}

TOSHI_NAMESPACE_END
