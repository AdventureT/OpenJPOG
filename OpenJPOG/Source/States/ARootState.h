#pragma once
#include "TKernel/TObject.h"
#include "GUI/AGUIGameHUD.h"

class ARootState : public Toshi::TObject
{
	DECLARE_DYNAMIC(ARootState)


public:
	ARootState();

	virtual ~ARootState() = default;
	// $JPOG: FUNCTION 0058e5e0
	//virtual void ProcessControllerLoss();
	//virtual void ProcessLostInput();
	//virtual void ProcessInput();
	//virtual void ProcessCommand();
	virtual TBOOL       OnUpdate(TFLOAT a_fDeltaTime) { return TTRUE; }
	// $JPOG: FUNCTION 0058df70
	virtual void        OnInsertion(){};
	// $JPOG: FUNCTION 0058df80
	virtual void        OnRemoval(){};
	virtual void        OnActivate();
	virtual void        OnDeactivate();
	// $JPOG: FUNCTION 0058e5d0
	virtual void        Render(){};
	virtual void        TransferControlTemporary(ARootState *a_pState);
	virtual void        TransferControl(ARootState *a_pState);
	virtual void        RemoveSelf();
	virtual ARootState *ReturnToState(const Toshi::TClass &a_rStateClass);
	virtual ARootState *ReturnToExactState(const Toshi::TClass &a_rStateClass);
	// $JPOG: FUNCTION 0058e590
	virtual TBOOL       ParentAllowed(ARootState &a_rParent) { return TTRUE; }
	// $JPOG: FUNCTION 0046e3d0
	virtual void        FlushUnitProxy(){};

	TBOOL       AddChild(ARootState &a_rState);
	TBOOL       RemoveChild();
	ARootState &GetCurrent();

private:
	void ExplicitDelete();

public:
	// $JPOG: FUNCTION 0046e3e0
	AGUIGameHUD &GetHUDState() { return m_oHUDState; }

protected:
	ARootState *m_pParent;     // 0x4
	ARootState *m_pChild;      // 0x8
	TBOOL       m_bAllowExit;  // 0xC
	TBOOL       m_bHasControl; // 0xE
	AGUIGameHUD m_oHUDState;   // 0x10
};
