#pragma once

#include "TObject.h"
#include "TNodeTree.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TTask : public TObject, public TNodeTree<TTask>::TNode
{
	DECLARE_DYNAMIC(TTask, TObject);

	enum State
	{
		State_Created = BITFIELD(0),
		State_Active = BITFIELD(1),
		State_Dying = BITFIELD(2),
	};

	friend class TScheduler;

public:
	virtual TBOOL Create();
	virtual TBOOL CreateFailed();
	virtual TBOOL OnCreate();
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime);
	virtual void OnDestroy();
	virtual TBOOL OnChildDying(TTask* child);
	virtual void OnChildDied(TClass* a_pClass, TTask* a_pDeletedTask);
	virtual void OnActivate();
	virtual void OnDeactivate();

	void Activate(TBOOL a_bActivate);

	TBOOL IsCreated() const { return HASFLAG(m_iState & State_Created); }
	TBOOL IsActive() const { return HASFLAG(m_iState & State_Active); }
	TBOOL IsDying() const { return HASFLAG(m_iState & State_Dying); }

private:
	TINT m_iState;
};

TOSHI_NAMESPACE_END