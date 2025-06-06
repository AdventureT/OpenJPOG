#include "TPCString.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_FREELIST(TPooledCString, 0, 8)

// $TKernelInterface: FUNCTION 10016980
TCStringPool::TCStringPool(TINT a_iMaxSize, TINT a_iInitialSize)
{
	m_iMaxSize        = a_iMaxSize;
	m_oPooledCStrings = TArray<TPooledCString>(a_iMaxSize, a_iInitialSize);
}

// $TKernelInterface: FUNCTION 10028000
TPCString TCStringPool::Get(TPCCHAR a_szString)
{
	if (!a_szString || TSystem::StringLength(a_szString) == 0) {
		return TPCString();
	}
	// I think this should be done with an Iterator and Begin() End()
	for (TINT i = 0; i < m_oPooledCStrings.GetNumElements(); i++) {
		if (m_oPooledCStrings[i].m_oString == a_szString) {
			// Already defined
			return TPCString(&m_oPooledCStrings[i]);
		}
	}
	TPooledCString *string = new TPooledCString(a_szString, this);
	m_oPooledCStrings.Push(*string);
	return TPCString(string);
}

// $TKernelInterface: FUNCTION 100281f0
TPCString TCStringPool::Get(TINT a_iInt)
{
	return Get(TCString().Format("%d", a_iInt));
}

// $TKernelInterface: FUNCTION 10028ee0
TPCString TCStringPool::Get(const TCString &a_sString)
{
	return Get(a_sString.GetString());
}

// $TKernelInterface: FUNCTION 10028d10
void TCStringPool::Remove(TPooledCString &a_rPooledCString)
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

TPooledCString::TPooledCString(TPCCHAR a_szString, TCStringPool *a_pStringPool)
{
	m_oString      = TCString(a_szString);
	m_pCStringPool = a_pStringPool;
}

// $TKernelInterface: FUNCTION 10028fd0
void TPooledCString::Delete()
{
	delete this;
}

// $TKernelInterface: FUNCTION 10029000
TPooledCString::~TPooledCString()
{
	if (m_pCStringPool) {
		m_pCStringPool->Remove(*this);
	}
}
