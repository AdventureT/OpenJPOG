#pragma once
#include "Defines.h"
#include <corecrt_malloc.h>
#include <stdio.h>
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

class TPCString;

class TKERNELINTERFACE_EXPORTS TCString 
{
public:
	
	friend TCString TOSHI_API operator+(TPCCHAR a_pLHS, const TCString& a_rRHS);

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

	TCString& Concat(TCString const& a_rString, TINT a_iLength = -1);
	TCString& Concat(TPCCHAR a_String, TINT a_iLength = -1);
	TINT Compare(TPCCHAR a_pcString, int a_iLength = -1) const;

	void Copy(const TCString& a_rOther, TINT a_iLength = -1);
	void Copy(TPCCHAR a_pcString, TINT a_iLength = -1);

	TCString& TOSHI_CALLBACKAPI Format(TPCCHAR a_pcFormat, ...);
	TINT Find(TCHAR a_cFind, TINT a_iIndex = 0) const;
	TINT FindReverse(TCHAR a_cFind, TINT a_iIndex = -1) const;

	void Truncate(TINT a_iLength);

	TBOOL IsIndexValid(TINT a_iIndex = 0) const
	{
		return a_iIndex <= m_iStrLen && a_iIndex >= 0;
	}

	TBOOL IsEmpty() const
	{
		return (TINT)m_iStrLen == 0;
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

	bool operator==(TPCCHAR a_pcString) const
	{
		return Compare(a_pcString) == 0;
	}

	bool operator==(const TCString& a_rOther) const
	{
		return Compare(a_rOther.m_pBuffer) == 0;
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

	TCString operator+(TPCCHAR a_pRHS) const
	{
		TCString str(*this);
		TASSERT(a_pRHS);
		return str.Concat(a_pRHS);
	}

	TCString operator+(const TCString& a_rRHS) const
	{
		TCString str(*this);
		return str.Concat(a_rRHS);
	}

	TCString& operator+=(TPCCHAR a_pcString)
	{
		Concat(a_pcString);
		return *this;
	}

	TCString& operator+=(TCString const& a_rString)
	{
		Concat(a_rString);
		return *this;
	}

	TCCHAR& operator[](TINT a_iIndex) const
	{
		TASSERT((a_iIndex>=0) && (a_iIndex<=(TINT)m_iStrLen));
		return m_pBuffer[a_iIndex];
	}

	TCHAR& operator[](TINT a_iIndex)
	{
		TASSERT((a_iIndex >= 0) && (a_iIndex <= (TINT)m_iStrLen));
		return m_pBuffer[a_iIndex];
	}

	const TCString& Print() const
	{
		TASSERT(GetString()!=TNULL);
		TDPRINTF("%s", GetString());
		return *this;
	}

	TINT ExcessLength() const { return m_iExcessLen; }
	TINT Length() const { return m_iStrLen; }

private:
	TBOOL AllocBuffer(TINT a_iLength, TBOOL a_bClear = TTRUE);

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

	inline static TCHAR m_aNull[4] = { 0, 0, 0, 0 };

	TPCHAR m_pBuffer;           // 0x0
	TINT m_iStrLen    : 24 = 0; // 0x4
	TINT m_iExcessLen : 8 = 0;  // 0x5
};

TCString TOSHI_API operator+(TPCCHAR a_pLHS, const TCString& a_rRHS);
TCString TOSHI_API operator+(const TCString& a_rLHS, const TPCString& a_rRHS);

TOSHI_NAMESPACE_END