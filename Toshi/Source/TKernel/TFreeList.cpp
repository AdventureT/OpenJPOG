#include "TFreeList.h"

TOSHI_NAMESPACE_USING

TFreeList::TFreeList()
{
	TASSERT(m_iGrowSize >= 0);
}
