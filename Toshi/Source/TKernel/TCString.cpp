#include "TCString.h"
#include "TDebug.h"

TOSHI_NAMESPACE_USING


TBOOL TCString::AllocBuffer(TINT m_iLength, TBOOL m_bClear)
{
	return TTRUE;
}

TINT TCString::Compare(TPCCHAR a_pcString, int a_iLength) const
{
	TASSERT(a_pcString!=TNULL);
	return TINT();
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
}
