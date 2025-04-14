#include "TLString.h"

TOSHI_NAMESPACE_USING

TFreeList TLocalisedString::m_oFreelist = TFreeList(sizeof(TLocalisedString), 0, 2000, (char *)"");
