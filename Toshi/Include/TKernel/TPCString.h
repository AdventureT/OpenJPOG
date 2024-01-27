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

	void Delete();

	~TPooledCString();

private:
	// 0x0 base (m_iRefCount)
	TCString m_oString;          // 0x4
	TCStringPool* m_pStringPool; // 0xC
};

class TKERNELINTERFACE_EXPORTS TPCString
{
public:

	static inline const TCString ms_sEmpty;

	TPCString()
	{
		m_pPCS = TNULL;
	}

	TPCString(const TPCString& a_rPCS) : TPCString()
	{
		if (a_rPCS.m_pPCS) {
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

	operator const TCString* () const
	{
		return m_pPCS ? &m_pPCS->m_oString : &ms_sEmpty;
	}

private:

	TPCString(TPooledCString* a_pPCS)
	{
		m_pPCS = a_pPCS;
		if (a_pPCS) {
			a_pPCS->IncRefCount();
		}
	}
	
	TPooledCString* m_pPCS;
};

class TKERNELINTERFACE_EXPORTS TCStringPool
{
	friend class TPooledCString;
public:
	TPCString Get(TPCCHAR a_szString);
protected:
	void Remove(TPooledCString& a_rPooledCString);

private:
	TArray<TPooledCString> m_oPooledCStrings;
};

TOSHI_NAMESPACE_END