#pragma once
#include "TKernel/TObject.h"
#include "GUI/AGUIGameHUD.h"

class ARootState : public Toshi::TObject
{
	DECLARE_DYNAMIC(ARootState)


public:

	virtual ~ARootState() = default;
	//virtual void ProcessControllerLoss();
	//virtual void ProcessLostInput();
	//virtual void ProcessInput();
	//virtual void ProcessCommand();
	virtual TBOOL OnUpdate(TFLOAT a_fDeltaTime) { return TTRUE; }
	virtual void OnInsertion() {};
	virtual void OnRemoval() {};
	virtual void OnActivate();
	virtual void OnDeactivate();
	virtual void Render() {};
	virtual void TransferControlTemporary(ARootState* a_pState);
	virtual void TransferControl(ARootState* a_pState);
	virtual void RemoveSelf();
	virtual ARootState* ReturnToState(const Toshi::TClass& a_rStateClass);
	virtual ARootState* ReturnToExactState(const Toshi::TClass& a_rStateClass);
	virtual TBOOL ParentAllowed(ARootState& a_rParent) { return TTRUE; }
	virtual void FlushUnitProxy() {};

	TBOOL AddChild(ARootState& a_rState);
	TBOOL RemoveChild();
	ARootState& GetCurrent();

private:

	void ExplicitDelete();

public:
	AGUIGameHUD& GetHUDState() { return m_oHUDState; }

private:
	ARootState* m_pParent;   // 0x4
	ARootState* m_pChild;    // 0x8
	TBOOL m_bHasControl;     // 0xE
	AGUIGameHUD m_oHUDState; // 0x10
};

