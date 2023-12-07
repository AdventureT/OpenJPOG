#pragma once
#include "TObject.h"
#include "THPTimer.h"
#include "TManagedPointer.h"
#include "TScheduler.h"

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
	TManagedPointer<TScheduler> m_pScheduler; // 0x30
	TFLOAT m_fDeltaTime;  // 0x44
	TFLOAT m_fAvgFPS;     // 0x48
};

TOSHI_NAMESPACE_END