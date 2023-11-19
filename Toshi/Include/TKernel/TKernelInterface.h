#pragma once
#include "TObject.h"
#include "TKernel/THPTimer.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TKernelInterface : public TObject
{
	DECLARE_DYNAMIC(TKernelInterface);
public:
	TKernelInterface(TINT argc, TPCHAR* const argv, TBOOL a_bVerbose);
	
	TBOOL Update();

	void DumpInfo();

	THPTimer* GetSystemTimer() { return &m_oSysTimer; }
private:
	THPTimer m_oSysTimer; // 0x8
};

TOSHI_NAMESPACE_END