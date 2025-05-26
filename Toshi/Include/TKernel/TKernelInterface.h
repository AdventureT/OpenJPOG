#pragma once
#include "Defines.h"
#include "TObject.h"
#include "THPTimer.h"
#include "TManagedPointer.h"
#include "TScheduler.h"
#include "TDLL.h"
#include "TNodeList.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TKernelInterfaceDLL : public TDLL
	, public TNodeList<TKernelInterfaceDLL>::TNode
{
public:
	// $TKernelInterface: FUNCTION 1001a8d0
	TKernelInterfaceDLL()
	{
	}

	virtual ~TKernelInterfaceDLL() = default;
};

template class TNodeList<TKernelInterfaceDLL>;

class TKERNELINTERFACE_EXPORTS TKernelInterface : public TObject
{
	DECLARE_DYNAMIC(TKernelInterface);

public:
	TKernelInterface(TINT argc, TPCHAR *const argv, TBOOL a_bVerbose);

	TBOOL Update();

	void                 DumpInfo();
	TKernelInterfaceDLL *FindInterface(const TCString &a_rszInterface);
	TKernelInterfaceDLL *LoadInterface(const TCString &a_rszInterface);
	void                 UnloadInterface(TKernelInterfaceDLL &a_rInterface);
	void                 UnloadInterface(const TCString &a_rszInterface);

	// $TKernelInterface: FUNCTION 1001a4d0
	THPTimer   *GetSystemTimer() { return &m_oSysTimer; }
	// $TKernelInterface: FUNCTION 1001a4e0
	TScheduler *GetScheduler() const { return m_pScheduler; }

private:
	THPTimer m_oSysTimer; // 0x8
	// TManagedPtr
	TScheduler                    *m_pScheduler; // 0x30
	TNodeList<TKernelInterfaceDLL> m_Interfaces; // 0x34
	TFLOAT                         m_fDeltaTime; // 0x44
	TFLOAT                         m_fAvgFPS;    // 0x48
	TBOOL                          m_bVerbose;   // 0x4C
};

TOSHI_NAMESPACE_END
