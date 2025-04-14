#pragma once

#include "ARootState.h"

class AFrontendState : public ARootState
{
	DECLARE_DYNAMIC(AFrontendState)

public:
	virtual ~AFrontendState() = default;
	virtual void  OnInsertion() override;
	virtual void  OnRemoval() override;
	virtual TBOOL ParentAllowed(ARootState &a_rParent) override;

protected:
	static inline int sm_iFERefCount = 0;
};
