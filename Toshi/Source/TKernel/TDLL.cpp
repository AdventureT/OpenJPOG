#include "TDLL.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

TPVOID TDLL::GetAddress(const TCString &a_rProcName)
{
	FARPROC pAddress = GetProcAddress(m_pDLL, a_rProcName);
	TASSERT(pAddress != TNULL);
	return pAddress;
}

TBOOL TDLL::Load(const TCString &a_rFileName)
{
	m_szFilename = a_rFileName;
	m_pDLL       = LoadLibrary(a_rFileName.GetString());
	TASSERT(m_pDLL != TNULL);
	return m_pDLL != TNULL;
}

void TDLL::Unload()
{
	if (m_pDLL != TNULL) {
		FreeLibrary(m_pDLL);
		m_szFilename = "";
		m_pDLL       = TNULL;
	}
}
