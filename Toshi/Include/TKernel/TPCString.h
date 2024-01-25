#pragma once
#include "TDebug.h"
#include "TCString.h"
#include "TFreeList.h"
#include "TRefCounted.h"
#include "TArray.h"

#define TCSTRINGPOOL_MAX_STRING_SIZE 1024

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TPCString
{

};

class TPooledCString;

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

class TKERNELINTERFACE_EXPORTS TPooledCString : public TRefCounted
{
	DECLARE_FREELIST(TPooledCString)
	
	friend class TCStringPool;

private:

	void Delete()
	{
		GetFreeList().Delete(this);
		delete this;
	}

	~TPooledCString()
	{
		if (m_pStringPool) {
			m_pStringPool->Remove(*this);
		}
	}

private:
	// 0x0 base (m_iRefCount)
	TCString m_oString;          // 0x4
	TCStringPool* m_pStringPool; // 0xC
};

TOSHI_NAMESPACE_END