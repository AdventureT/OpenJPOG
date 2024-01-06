#pragma once
#include "Defines.h"
#include <corecrt_malloc.h>
#include <stdio.h>
#include "TDebug.h"
#include "TSystemTools.h"
#include <TKernel/TMemory.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TWString
{
public:

	TWString()
	{
		Reset();
		AllocBuffer(0);
	}

	TWString(TINT a_iLength)
	{
		Reset();
		AllocBuffer(a_iLength);
	}

	TWString(const TWString& a_rOther)
	{
		Reset();
		Copy(a_rOther);
	}

	TWString(TPCWCHAR a_pcString)
	{
		Reset();
		Copy(a_pcString);
	}

	~TWString()
	{
		FreeBuffer();
	}

	TWString& Concat(TWString const& a_rString, TINT a_iLength = -1);
	TWString& Concat(TPCWCHAR a_String, TINT a_iLength = -1);
	TINT Compare(TPCWCHAR a_pcString, int a_iLength = -1) const;

	void Copy(const TWString& a_rOther, TINT a_iLength = -1);
	void Copy(TPCWCHAR a_pcString, TINT a_iLength = -1);

	TWString& TOSHI_CALLBACKAPI Format(TPCWCHAR a_pcFormat, ...);
	TINT Find(TWCHAR a_cFind, TINT a_iIndex = 0) const;

	void Truncate(TINT a_iLength);

	TBOOL IsIndexValid(TINT a_iIndex = 0) const
	{
		return a_iIndex <= m_iStrLen && a_iIndex >= 0;
	}

	TPCWCHAR GetString(TINT a_iIndex = 0) const
	{
		return IsIndexValid(a_iIndex) ? m_pBuffer + a_iIndex : TNULL;
	}

	bool operator!=(TPCWCHAR a_pcString) const
	{
		return Compare(a_pcString) != 0;
	}

	bool operator!=(const TWString& a_rOther) const
	{
		return Compare(a_rOther.m_pBuffer) != 0;
	}

	bool operator==(TPCWCHAR a_pcString) const
	{
		return Compare(a_pcString) == 0;
	}

	bool operator==(const TWString& a_rOther) const
	{
		return Compare(a_rOther.m_pBuffer) == 0;
	}

	TWString& operator=(TPCWCHAR a_pcString)
	{
		Copy(a_pcString);
		return *this;
	}

	TWString& operator=(TWString& a_rOther)
	{
		Copy(a_rOther);
		return *this;
	}

	operator TPWCHAR() const
	{
		return m_pBuffer;
	}

	TWString& operator+=(TPCWCHAR a_pcString)
	{
		Concat(a_pcString);
		return *this;
	}

	TWString& operator+=(TWString const& a_rString)
	{
		Concat(a_rString);
		return *this;
	}

	TWCHAR& operator[](TINT a_iIndex) const
	{
		TASSERT(a_iIndex <= (int) m_iStrLen);
		return m_pBuffer[a_iIndex];
	}

	TWCHAR& operator[](TINT a_iIndex)
	{
		TASSERT(a_iIndex <= (int)m_iStrLen);
		return m_pBuffer[a_iIndex];
	}

	const TWString& Print() const
	{
		TASSERT(GetString() != TNULL);
		TDPRINTF("%s", TSystem::StringUnicodeToChar(TSystem::GetTempCString(), GetString(), 0x400));
		return *this;
	}

	TINT ExcessLength() const { return m_iExcessLen; }
	TINT Length() const { return m_iStrLen; }

private:

	TBOOL AllocBuffer(TINT a_iLength, TBOOL a_bClear = TTRUE);

	void FreeBuffer()
	{
		if (m_iStrLen != 0) {
			tfree(m_pBuffer);
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

	inline static TWCHAR m_aNull[4] = { 0, 0, 0, 0 };

	TPWCHAR m_pBuffer;          // 0x0
	TINT m_iExcessLen : 8 = 0;  // 0x4
	TINT m_iStrLen : 24 = 0;    // 0x5
};

TOSHI_NAMESPACE_END