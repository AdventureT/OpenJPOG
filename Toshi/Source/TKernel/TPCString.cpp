#include "TPCString.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_FREELIST(TPooledCString, 0, 8)

TCStringPool::TCStringPool(TINT a_iMaxSize, TINT a_iInitialSize)
{
	m_iMaxSize = a_iMaxSize;
	m_oPooledCStrings = TArray<TPooledCString>(a_iMaxSize, a_iInitialSize);
}

TPCString TCStringPool::Get(TPCCHAR a_szString)
{
	if (!a_szString || TSystem::StringLength(a_szString) == 0) {
		return TPCString();
	}
	TPooledCString* string = new TPooledCString(a_szString, this);
	m_oPooledCStrings.Push(*string);
	return TPCString(string);
}

void TCStringPool::Remove(TPooledCString& a_rPooledCString)
{
	TASSERT(a_rPooledCString.GetRefCount() == 0);
	//auto iter = TArray<TPooledCString>::Iterator(-1, a_rPooledCString);
	//TASSERT(iter != m_oPooledCStrings.End());
	m_oPooledCStrings.Pop();
}

TPooledCString::TPooledCString()
{
	m_pCStringPool = TNULL;
}

TPooledCString::TPooledCString(TPCCHAR a_szString, TCStringPool* a_pStringPool)
{
	m_oString = TCString(a_szString);
	m_pCStringPool = a_pStringPool;
}

void TPooledCString::Delete()
{
	delete this;
}

TPooledCString::~TPooledCString()
{
	if (m_pCStringPool) {
		m_pCStringPool->Remove(*this);
	}
}
