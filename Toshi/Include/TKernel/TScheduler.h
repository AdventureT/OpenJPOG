#pragma once

#include "TObject.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TScheduler : public TObject
{
	DECLARE_DYNAMIC(TKernelInterface);
public:
	void Update();
};

TOSHI_NAMESPACE_END