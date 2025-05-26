#include "TDLL.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

// $TKernelInterface: FUNCTION 1000cb00
TPVOID TDLL::GetAddress(const TCString &a_rProcName)
{
	FARPROC pAddress = GetProcAddress(m_pDLL, a_rProcName);
	TASSERT(pAddress != TNULL);
	return pAddress;
}

// $TKernelInterface: FUNCTION 1000ca40
TBOOL TDLL::Load(const TCString &a_rFileName)
{
	m_szFilename = a_rFileName;
	m_pDLL       = LoadLibrary(a_rFileName.GetString());
	TASSERT(m_pDLL != TNULL);
	return m_pDLL != TNULL;
}

// $TKernelInterface: FUNCTION 1000cad0
void TDLL::Unload()
{
	if (m_pDLL != TNULL) {
		FreeLibrary(m_pDLL);
		m_szFilename = "";
		m_pDLL       = TNULL;
	}
}
