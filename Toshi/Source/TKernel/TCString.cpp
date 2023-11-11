#include "TCString.h"
#include "TDebug.h"
#include "TSystem.h"
#include <string.h>

TOSHI_NAMESPACE_USING


TBOOL TCString::AllocBuffer(TINT a_iLength, TBOOL a_bClear)
{
	TASSERT(a_iLength >= 0);

	TBOOL hasChanged = TFALSE;

	if (a_iLength != m_iStrLen) {
		if (a_iLength == 0) {
			if (a_bClear) free(m_pBuffer);

			m_pBuffer = m_aNull;
			hasChanged = TTRUE;
			m_iExcessLen = 0;
		}
		else {
			TINT newExcessLen = (m_iStrLen - a_iLength) + m_iExcessLen;

			if (newExcessLen < 0 || newExcessLen > 0xFF) {
				if (m_iStrLen != 0 && a_bClear) {
					free(m_pBuffer);
				}
				m_pBuffer = (TPCHAR)malloc(a_iLength + 1);
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
	if (a_bClear) m_pBuffer[0] = 0;
	return hasChanged;
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
	if (*this != a_rOther)
	{
		if (m_iStrLen < a_iLength || a_iLength == -1) a_iLength = m_iStrLen;
		AllocBuffer(a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}

void TCString::Copy(TPCCHAR a_pcString, TINT a_iLength)
{
	if (m_pBuffer != a_pcString)
	{
		TINT iLength = a_pcString ? TSystem::StringLength(a_pcString) : 0;
		if (iLength < a_iLength || a_iLength == -1) a_iLength = iLength;
		AllocBuffer(a_iLength, TTRUE);
		TSystem::MemCopy(m_pBuffer, a_pcString, a_iLength);
		m_pBuffer[a_iLength] = '\0';
	}
}
