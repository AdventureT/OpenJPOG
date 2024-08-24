#include "TCString.h"
#include "TSystemTools.h"
#include <string.h>
#include <TKernel/TMemory.h>
#include "TWString.h"
#include "TPCString.h"

TOSHI_NAMESPACE_BEGIN

TBOOL TCString::AllocBuffer(TINT a_iLength, TBOOL a_bClear)
{
	TASSERT(a_iLength >= 0);

	TBOOL hasChanged = TFALSE;

	if (a_iLength != m_iStrLen) {
		if (a_iLength == 0) {
			if (a_bClear) tfree(m_pBuffer);

			m_pBuffer = m_aNull;
			hasChanged = TTRUE;
			m_iExcessLen = 0;
		}
		else {
			TINT newExcessLen = (m_iStrLen - a_iLength) + m_iExcessLen;

			if (newExcessLen < 0 || newExcessLen > 0xFF) {
				if (m_iStrLen != 0 && a_bClear) tfree(m_pBuffer);
				
				m_pBuffer = (TPCHAR)tmalloc(a_iLength + 1, TNULL, -1);
				m_iExcessLen = 0;
				TASSERT(m_pBuffer!=TNULL);
				hasChanged = TTRUE;
			}
			else {
				m_iExcessLen = newExcessLen;
				hasChanged = TFALSE;
			}
		}
		m_iStrLen = a_iLength;
	}
	if (a_bClear) m_pBuffer[0] = '\0';
	return hasChanged;
}

TCString& TCString::Concat(TCString const& a_rString, TINT a_iLength)
{
	TINT len = a_rString.Length();
	if (len < a_iLength || a_iLength == -1) {
		a_iLength = len;
	}
	TPCHAR pBuffer = m_pBuffer;
	len = Length();
	TBOOL ret = AllocBuffer(len + a_iLength, TFALSE);
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

TCString& TCString::Concat(TPCCHAR a_String, TINT a_iLength)
{
	TINT len = TSystem::StringLength(a_String);
	if (len < a_iLength || a_iLength == -1) {
		a_iLength = len;
	}
	TPCHAR pBuffer = m_pBuffer;
	len = Length();
	TBOOL ret = AllocBuffer(len + a_iLength, TFALSE);
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

TINT TCString::Compare(TPCCHAR a_pcString, int a_iLength) const
{
	TASSERT(a_pcString!=TNULL);
	TASSERT(GetString()!=TNULL);
	if (a_iLength != -1)
	{
		return strncmp(GetString(), a_pcString, a_iLength);
	}
	return strcmp(GetString(), a_pcString);
}

void TCString::Copy(const TCString& a_rOther, TINT a_iLength)
{
	if (*this != a_rOther) {
		if (a_rOther.m_iStrLen < a_iLength || a_iLength == -1) a_iLength = a_rOther.m_iStrLen;
		AllocBuffer(a_iLength);
		TSystem::MemCopy(m_pBuffer, a_rOther.m_pBuffer, a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}

void TCString::Copy(const TWString &a_rOther, TINT a_iLength)
{
	if (a_rOther.Length() < a_iLength || a_iLength == -1) a_iLength = a_rOther.Length();
	AllocBuffer(a_iLength);
	TSystem::StringUnicodeToChar(m_pBuffer, a_rOther, a_iLength);
	m_pBuffer[a_iLength] = '\0';
}

void TCString::Copy(TPCCHAR a_pcString, TINT a_iLength)
{
	if (m_pBuffer != a_pcString) {
		TINT iLength = a_pcString ? TSystem::StringLength(a_pcString) : 0;
		if (iLength < a_iLength || a_iLength == -1) a_iLength = iLength;
		AllocBuffer(a_iLength, TTRUE);
		TSystem::MemCopy(m_pBuffer, a_pcString, a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}

TCString& TOSHI_CALLBACKAPI TCString::Format(TPCCHAR a_pcFormat, ...)
{
	char buffer[0x400];
	va_list vargs;
	va_start(vargs, a_pcFormat);
	_vsnprintf(buffer, sizeof(buffer), a_pcFormat, vargs);
	va_end(vargs);
	Copy(buffer);
	return *this;
}

TINT TCString::Find(TCHAR a_cFind, TINT a_iIndex) const
{
	if (!IsIndexValid(a_iIndex)) return -1;
	TPCCHAR foundAt = strchr(GetString() + a_iIndex, a_cFind);
	if (foundAt == TNULL) return -1;

	return foundAt - GetString();
}

void TCString::Truncate(TINT a_iLength)
{
	TINT len = Length();
	if (len < a_iLength) {
		a_iLength = len;
	}
	TPCHAR pBuffer = m_pBuffer;
	TBOOL ret = AllocBuffer(a_iLength, TFALSE);
	if (ret) {
		TSystem::StringCopy(m_pBuffer, pBuffer, a_iLength);
	}
	m_pBuffer[a_iLength] = '\0';
	if (ret && len != 0) {
		tfree(pBuffer);
	}
}

TINT TCString::FindReverse(TCHAR a_cFind, TINT a_iIndex /*= -1*/) const
{
	if (a_iIndex == -1) {
		a_iIndex = m_iStrLen;
	}
	else if (!IsIndexValid(a_iIndex)) {
		return -1;
	}
	
	if (a_iIndex < 0) {
		return -1;
	}

	TINT iBytesLeft = a_iIndex;
	const TCHAR* pchString = GetString(0);

	// Look for the character by checking 5 bytes sequences
	for (; iBytesLeft > 5; iBytesLeft -= 5)
	{
		if ( pchString[iBytesLeft - 0] == a_cFind ) return iBytesLeft - 0;
		if ( pchString[iBytesLeft - 1] == a_cFind ) return iBytesLeft - 1;
		if ( pchString[iBytesLeft - 2] == a_cFind ) return iBytesLeft - 2;
		if ( pchString[iBytesLeft - 3] == a_cFind ) return iBytesLeft - 3;
		if ( pchString[iBytesLeft - 4] == a_cFind ) return iBytesLeft - 4;
	}

	// Check the left bytes
	for (; iBytesLeft > 0; iBytesLeft--)
	{
		if ( pchString[iBytesLeft] == a_cFind )
			return iBytesLeft;
	}

	return -1;
}

TCString TCString::Mid(TINT a_iFirst, TINT a_iCount) const
{
	if (a_iFirst < 0) {
		a_iFirst = 0;
	}
	else if (Length() <= a_iFirst) {
		// Can't return string bigger that the original
		return TCString();
	}

	if (a_iCount < 0 || Length() < a_iFirst + a_iCount) {
		a_iCount = Length() - a_iFirst;
	}

	TCString strResult(a_iCount);
	TSystem::MemCopy((TPVOID)(TPCCHAR)strResult, GetString(a_iFirst), a_iCount);
	strResult[a_iCount] = '\0';

	return strResult;
}

TCString TOSHI_API operator+(TPCCHAR a_pLHS, const TCString& a_rRHS)
{
	TCString str(a_pLHS);
	TASSERT(a_pLHS);
	return str.Concat(a_rRHS);
}

TCString TOSHI_API operator+(const TCString& a_rLHS, const TPCString& a_rRHS)
{
	return TCString(a_rLHS) += a_rRHS.GetCString();
}

TOSHI_NAMESPACE_END