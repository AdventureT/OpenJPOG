#include "TLString.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

TFreeList TLocalisedString::m_oFreelist = TFreeList(sizeof(TLocalisedString), 0, 2000, (char *)"");
