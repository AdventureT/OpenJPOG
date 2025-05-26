#pragma once
#include <TKernel/TCString.h>
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TDLL
{
public:
	// $TKernelInterface: FUNCTION 1000cba0
	TDLL()
	{
		m_pDLL = TNULL;
	}

	// $TKernelInterface: FUNCTION 1000cb80
	virtual ~TDLL()
	{
		Unload();
	}

	TPVOID GetAddress(const TCString &a_rProcName);
	TBOOL  Load(const TCString &a_rFileName);
	void   Unload();

	// $TKernelInterface: FUNCTION 1000cb60
	HMODULE         GetDLL() { return m_pDLL; }

	// $TKernelInterface: FUNCTION 1000cb70
	const TCString &GetFilename() { return m_szFilename; }

private:
	TCString m_szFilename; // 0x4
	HMODULE  m_pDLL;       // 0xC
};

TOSHI_NAMESPACE_END
