#pragma once

#include "TObject.h"
#include "TNodeTree.h"

TOSHI_NAMESPACE_BEGIN

//class TScheduler;

class TKERNELINTERFACE_EXPORTS TTask : public TObject
	, public TNodeTree<TTask>::TNode
{
	DECLARE_DYNAMIC(TTask);

	enum State
	{
		State_Created = BITFIELD(0),
		State_Active  = BITFIELD(1),
		State_Dying   = BITFIELD(2),
	};

	friend class TScheduler;

public:
	// $TKernelInterface: FUNCTION 1002e7a0 INCOMPLETE
	TTask()
	{
		m_Flags      = 0;
		m_pScheduler = TNULL;
	}

	virtual TBOOL Create();
	virtual TBOOL CreateFailed();
	// $TKernelInterface: FUNCTION 1002ea60
	virtual TBOOL OnCreate() { return TTRUE; }
	// $TKernelInterface: FUNCTION 1002ea50
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) { return TTRUE; }
	// $TKernelInterface: FUNCTION 1002ea40
	virtual void  OnDestroy() {}
	// $TKernelInterface: FUNCTION 1002ea30
	virtual TBOOL OnChildDying(TTask *child) { return TTRUE; }
	// $TKernelInterface: FUNCTION 1002ea20
	virtual void  OnChildDied(TClass *a_pClass, TTask *a_pDeletedTask) {}
	// $TKernelInterface: FUNCTION 1002ea10
	virtual void  OnActivate() {}
	// $TKernelInterface: FUNCTION 1002ea00
	virtual void  OnDeactivate() {}

	void Activate(TBOOL a_bActivate);
	void DestroyTask();

	// $TKernelInterface: FUNCTION 1002eaa0
	TBOOL IsCreated() const { return HASFLAG(m_Flags & State_Created); }
	// $TKernelInterface: FUNCTION 1002ea90
	TBOOL IsActive() const { return HASFLAG(m_Flags & State_Active); }
	// $TKernelInterface: FUNCTION 1002ea80
	TBOOL IsDying() const { return HASFLAG(m_Flags & State_Dying); }

	TScheduler *GetScheduler();

private:
	TINT        m_Flags;
	TScheduler *m_pScheduler; // 0x20
};

TOSHI_NAMESPACE_END
