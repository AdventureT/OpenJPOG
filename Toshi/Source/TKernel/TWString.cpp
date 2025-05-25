#include "TWString.h"
#include "TSystemTools.h"
#include <string.h>

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 10031740
TBOOL TWString::AllocBuffer(TINT a_iLength, TBOOL a_bClear)
{
	TASSERT(a_iLength >= 0);

	TBOOL hasChanged = TFALSE;

	if (a_iLength != m_iStrLen) {
		if (a_iLength == 0) {
			if (a_bClear) tfree(m_pBuffer);

			m_pBuffer    = m_aNull;
			hasChanged   = TTRUE;
			m_iExcessLen = 0;
		}
		else {
			TINT newExcessLen = (m_iStrLen - a_iLength * 2) + m_iExcessLen;

			if (newExcessLen < 0 || newExcessLen > 0xFF) {
				if (m_iStrLen != 0 && a_bClear) tfree(m_pBuffer);

				m_pBuffer    = (TPWCHAR)tmalloc((a_iLength + 1) * 2);
				m_iExcessLen = 0;
				TASSERT(m_pBuffer != TNULL);
				hasChanged = TTRUE;
			}
			else {
				m_iExcessLen = newExcessLen;
				hasChanged   = TFALSE;
			}
		}
		m_iStrLen = a_iLength;
	}
	if (a_bClear) m_pBuffer[0] = '\0';
	return hasChanged;
}

TWString &TWString::Concat(TWString const &a_rString, TINT a_iLength)
{
	TINT len = a_rString.Length();
	if (len < a_iLength || a_iLength == -1) {
		a_iLength = len;
	}
	TPWCHAR pBuffer = m_pBuffer;
	len             = Length();
	TBOOL ret       = AllocBuffer(len + a_iLength, TFALSE);
	if (ret) {
		TSystem::StringCopy(m_pBuffer, pBuffer, -1);
	}
	TSystem::StringCopy(&m_pBuffer[len], a_rString.m_pBuffer, a_iLength);
	m_pBuffer[len + a_iLength] = '\0';
	if (ret && len != 0) {
		tfree(pBuffer);
	}
	return *this;
}

TWString &TWString::Concat(TPCWCHAR a_String, TINT a_iLength)
{
	TINT len = TSystem::StringLength(a_String);
	if (len < a_iLength || a_iLength == -1) {
		a_iLength = len;
	}
	TPWCHAR pBuffer = m_pBuffer;
	len             = Length();
	TBOOL ret       = AllocBuffer(len + a_iLength, TFALSE);
	if (ret) {
		TSystem::StringCopy(m_pBuffer, pBuffer, -1);
	}
	TSystem::StringCopy(&m_pBuffer[len], a_String, a_iLength);
	m_pBuffer[len + a_iLength] = '\0';
	if (ret && len != 0) {
		tfree(pBuffer);
	}
	return *this;
}

// $TKernelInterface: FUNCTION 100310b0
TINT TWString::Compare(TPCWCHAR a_pcString, int a_iLength) const
{
	TASSERT(a_pcString != TNULL);
	TASSERT(GetString() != TNULL);
	if (a_iLength != -1)
	{
		return wcsncmp(GetString(), a_pcString, a_iLength);
	}
	return wcscmp(GetString(), a_pcString);
}

void TWString::Copy(const TWString &a_rOther, TINT a_iLength)
{
	if (*this != a_rOther) {
		if (a_rOther.m_iStrLen < a_iLength || a_iLength == -1) a_iLength = a_rOther.m_iStrLen;
		AllocBuffer(a_iLength);
		TSystem::StringCopy(m_pBuffer, a_rOther.m_pBuffer, a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}

void TWString::Copy(TPCWCHAR a_pcString, TINT a_iLength)
{
	if (m_pBuffer != a_pcString) {
		TINT iLength = a_pcString ? TSystem::StringLength(a_pcString) : 0;
		if (iLength < a_iLength || a_iLength == -1) a_iLength = iLength;
		AllocBuffer(a_iLength, TTRUE);
		TSystem::StringCopy(m_pBuffer, a_pcString, a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}

void TWString::Copy(TPCCHAR a_pcString, TINT a_iLength)
{
	TINT iLength = a_pcString ? TSystem::StringLength(a_pcString) : 0;
	if (iLength < a_iLength || a_iLength == -1) {
		a_iLength = iLength;
	}
	AllocBuffer(a_iLength, TTRUE);
	TSystem::StringCharToUnicode(m_pBuffer, a_pcString, a_iLength);
	m_pBuffer[a_iLength] = L'\0';
}

// $TKernelInterface: FUNCTION 10030e20
TWString &TOSHI_CALLBACKAPI TWString::Format(TPCWCHAR a_pcFormat, ...)
{
	TWCHAR  buffer[0x400];
	va_list vargs;
	va_start(vargs, a_pcFormat);
	_vsnwprintf(buffer, sizeof(buffer), a_pcFormat, vargs);
	va_end(vargs);
	Copy(buffer);
	return *this;
}

// $TKernelInterface: FUNCTION 10031390
TINT TWString::Find(TWCHAR a_cFind, TINT a_iIndex) const
{
	if (!IsIndexValid(a_iIndex)) return -1;
	TPCWCHAR foundAt = wcschr(GetString() + a_iIndex, a_cFind);
	if (foundAt == TNULL) return -1;

	return foundAt - GetString() >> 1;
}

// $TKernelInterface: FUNCTION 10031520
void TWString::Truncate(TINT a_iLength)
{
	TINT len = Length();
	if (len < a_iLength) {
		a_iLength = len;
	}
	TPWCHAR pBuffer = m_pBuffer;
	TBOOL   ret     = AllocBuffer(a_iLength, TFALSE);
	if (ret) {
		TSystem::StringCopy(m_pBuffer, pBuffer, a_iLength);
	}
	m_pBuffer[a_iLength] = '\0';
	if (ret && len != 0) {
		tfree(pBuffer);
	}
}
