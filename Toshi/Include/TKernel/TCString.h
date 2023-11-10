#include "Defines.h"
#include <corecrt_malloc.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TCString 
{
public:

	TCString()
	{
		Reset();
		AllocBuffer(0);
	}

	TCString(TINT a_iLength)
	{
		Reset();
		AllocBuffer(a_iLength);
	}

	TCString(const TCString &a_rOther)
	{
		Reset();
		Copy(a_rOther);
	}

	TCString(TPCCHAR a_pcString)
	{
		Reset();
		Copy(a_pcString);
	}

	~TCString()
	{
		FreeBuffer();
	}

	TINT Compare(TPCCHAR a_pcString, int a_iLength = -1) const;

	void Copy(const TCString& a_rOther, TINT a_iLength = -1);
	void Copy(TPCCHAR a_pcString, TINT a_iLength = -1);


	TBOOL IsIndexValid(TINT a_iIndex = 0) const
	{
		return a_iIndex <= m_iStrLen && a_iIndex >= 0;
	}

	TPCCHAR GetString(TINT a_iIndex = 0) const
	{
		return IsIndexValid(a_iIndex) ? m_pBuffer + a_iIndex : TNULL;
	}

	bool operator!=(TPCCHAR a_pcString) const
	{
		return Compare(a_pcString) != 0;
	}

	bool operator!=(const TCString& a_rOther) const
	{
		return Compare(a_rOther.m_pBuffer) != 0;
	}

	TCString& operator=(TPCCHAR a_pcString)
	{
		Copy(a_pcString);
		return *this;
	}

	TCString& operator=(TCString& a_rOther)
	{
		Copy(a_rOther);
		return *this;
	}

	operator TPCCHAR() const
	{
		return m_pBuffer;
	}

	TCString& operator+=(TPCCHAR a_pcString)
	{
		return *this;
	}

private:

	TBOOL AllocBuffer(TINT m_iLength, TBOOL m_bClear = TTRUE);

	void FreeBuffer()
	{
		if (m_iStrLen != 0)
		{
			free(m_pBuffer);
			m_pBuffer = TNULL;
		}
		Reset();
	}

	void Reset()
	{
		m_pBuffer = m_aNull;
		m_iExcessLen = 0;
		m_iStrLen = 0;
	}

private:

	inline static char* m_aNull = TNULL;

	TPCHAR m_pBuffer;           // 0x0
	TUINT m_iExcessLen : 8 = 0; // 0x4
	TUINT m_iStrLen : 24 = 0;   // 0x5
};

TOSHI_NAMESPACE_END