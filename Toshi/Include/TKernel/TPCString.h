#pragma once
#include "TDebug.h"
#include "TCString.h"
#include "TFreeList.h"
#include "TRefCounted.h"
#include "TArray.h"

#define TCSTRINGPOOL_MAX_STRING_SIZE 1024

TOSHI_NAMESPACE_BEGIN

class TCStringPool;

class TKERNELINTERFACE_EXPORTS TPooledCString : public TRefCounted
{
	DECLARE_FREELIST(TPooledCString)

	friend class TCStringPool;
	friend class TPCString;

private:
	TPooledCString();
	TPooledCString(TPCCHAR a_szString, TCStringPool *a_pStringPool);

	void Delete();

	~TPooledCString();

private:
	// 0x0 base (m_iRefCount)
	TCString      m_oString;      // 0x4
	TCStringPool *m_pCStringPool; // 0xC
};

class TKERNELINTERFACE_EXPORTS TPCString
{
public:
	friend class TCStringPool;
	static inline const TCString ms_sEmpty;

	TPCString()
	{
		m_pPCS = TNULL;
	}

	TPCString(const TPCString &a_rPCS)
		: TPCString()
	{
		if (a_rPCS.m_pPCS) {
			m_pPCS = a_rPCS.m_pPCS;
			a_rPCS.m_pPCS->IncRefCount();
		}
	}

	~TPCString()
	{
		if (m_pPCS) {
			if (m_pPCS->DecRefCount() == 0) {
				m_pPCS->Delete();
			}
			m_pPCS = TNULL;
		}
	}

	TINT Compare(const TPCString &a_rString) const
	{
		if (!GetPtr() && a_rString.GetPtr()) {
			return -1;
		}
		if (GetPtr() && !a_rString.GetPtr()) {
			return 1;
		}
		if (GetPtr() != a_rString.GetPtr()) {
			return a_rString.GetPtr()->m_oString.Compare(GetPtr()->m_oString.GetString());
		}
		return 0;
	}

	TBOOL IsEmpty() const
	{
		if (!GetPtr()) {
			return TTRUE;
		}
		return GetCString().IsEmpty();
	}

	TBOOL operator!=(const TPCString &a_rString) const
	{
		return GetPtr() != a_rString.GetPtr();
	}

	const TCString &operator*() const
	{
		return m_pPCS ? m_pPCS->m_oString : ms_sEmpty;
	}

	const TCString *operator->() const
	{
		return m_pPCS ? &m_pPCS->m_oString : &ms_sEmpty;
	}

	TBOOL operator<(const TPCString &a_rString) const
	{
		return Compare(a_rString) == 0;
	}

	TBOOL operator==(const TPCString &a_rString) const
	{
		return GetPtr() == a_rString.GetPtr();
	}

	TPCString &operator=(const TPCString &a_rString)
	{
		if (GetPtr() != a_rString.GetPtr()) {
			if (GetPtr() && GetPtr()->DecRefCount() == 0) {
				GetPtr()->Delete();
			}
			m_pPCS = a_rString.GetPtr();
			a_rString.GetPtr()->IncRefCount();
		}
		return *this;
	}

	operator const TCString *() const
	{
		return GetPtr() ? &GetPtr()->m_oString : &ms_sEmpty;
	}

	TPooledCString *GetPtr() const
	{
		return m_pPCS;
	}

	const TCString &GetCString() const
	{
		return GetPtr() ? GetPtr()->m_oString : ms_sEmpty;
	}

	TCStringPool *GetStringPool() const
	{
		return GetPtr()->m_pCStringPool;
	}

	TCString &GetVolatileCString() const
	{
		TASSERT(GetPtr() != TNULL);
		TASSERT(GetPtr()->m_pCStringPool == TNULL);
		return GetPtr()->m_oString;
	}

private:
	TPCString(TPooledCString *a_pPCS)
	{
		m_pPCS = a_pPCS;
		if (a_pPCS) {
			a_pPCS->IncRefCount();
		}
	}

	TPooledCString *m_pPCS;
};

class TKERNELINTERFACE_EXPORTS TCStringPool
{
	friend class TPooledCString;

public:
	TCStringPool()
		: TCStringPool(0x400, 0) {}

	TCStringPool(TINT a_iMaxSize, TINT a_iInitialSize);

	TPCString Get(TPCCHAR a_szString);
	TPCString Get(TINT a_iInt);

protected:
	void Remove(TPooledCString &a_rPooledCString);

private:
	TINT                   m_iMaxSize;        // 0x0
	TArray<TPooledCString> m_oPooledCStrings; // 0x4
};

TOSHI_NAMESPACE_END
