#include "TGUIInterface.h"
#include "TWString.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TGUIInterface, TObject);

void TGUIInterface::Create()
{
	m_oActionMap.Create();
	m_oActionMap.AddActionMapping(0x10001, 0x200);
	m_oActionMap.AddActionMapping(0x10002, 0x400);
	m_oActionMap.AddActionMapping(0x10003, 0x800);
	m_oActionMap.AddActionMapping(0x10004, 0x1000);
	m_oActionMap.AddActionMapping(0x10011, 0x200);
	m_oActionMap.AddActionMapping(0x10012, 0x400);
	m_oActionMap.AddActionMapping(0x10013, 0x800);
	m_oActionMap.AddActionMapping(0x10014, 0x1000);
	m_oActionMap.AddActionMapping(0x20072, 0x200);
	m_oActionMap.AddActionMapping(0x20075, 0x400);
	m_oActionMap.AddActionMapping(0x20077, 0x800);
	m_oActionMap.AddActionMapping(0x20074, 0x1000);
	m_oActionMap.AddActionMapping(0x20015, 0x200);
	m_oActionMap.AddActionMapping(0x20024, 0x400);
	m_oActionMap.AddActionMapping(0x20023, 0x800);
	m_oActionMap.AddActionMapping(0x20022, 0x1000);
	m_oActionMap.AddActionMapping(0x10009, 2);
	m_oActionMap.AddActionMapping(0x1000b, 1);
	m_oActionMap.AddActionMapping(0x1000b, 0x10000);
	m_oActionMap.AddActionMapping(0x3000b, 0x2000);
	m_oActionMap.AddActionMapping(0x30001, 0x4000);
	m_oActionMap.AddActionMapping(0x30002, 0x8000);
	m_oActionMap.AddActionMapping(0x2003d, 1);
	m_oActionMap.AddActionMapping(0x20020, 1);
	m_oActionMap.AddActionMapping(0x2006a, 1);
	m_oActionMap.AddActionMapping(0x20012, 2);
	m_oActionMap.AddActionMapping(0x20005, 2);
}

void TGUIInterface::Error(const TCString &a_rText)
{
	TWString().Format(L"Runtime error in TGUIInterface:\n\t%s\n", TWString(a_rText)).Print();
	// Throw event
}

TOSHI_NAMESPACE_END
