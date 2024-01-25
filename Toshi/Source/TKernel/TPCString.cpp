#include "TPCString.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_FREELIST(TPooledCString, 0, 8)

TPCString TCStringPool::Get(TPCCHAR a_szString)
{
	if (!a_szString || TSystem::StringLength(a_szString) == 0) {
		return TPCString();
	}
	return TPCString();
}

void TCStringPool::Remove(TPooledCString& a_rPooledCString)
{
	TASSERT(a_rPooledCString.GetRefCount() == 0);
	//auto iter = TArray<TPooledCString>::Iterator(-1, a_rPooledCString);
	//TASSERT(iter != m_oPooledCStrings.End());
	m_oPooledCStrings.Pop();
}
