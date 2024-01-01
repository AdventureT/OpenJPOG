#pragma once
#include <TKernel/TCString.h>
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TDLL
{
public:

	TDLL()
	{
		m_pDLL = TNULL;
	}

	virtual ~TDLL()
	{
		Unload();
	}

	TPVOID GetAddress(const TCString &a_rProcName);
	TBOOL Load(const TCString& a_rFileName);
	void Unload();

	HMODULE GetDLL() { return m_pDLL; }
	const TCString& GetFilename() { return m_szFilename; }
private:
	TCString m_szFilename; // 0x4
	HMODULE m_pDLL;        // 0xC
};

TOSHI_NAMESPACE_END