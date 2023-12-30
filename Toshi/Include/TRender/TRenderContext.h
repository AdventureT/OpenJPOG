#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TKernelInterface.h"

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;

class TOSHI_EXPORT TRenderContext
{
private:
	TRenderInterface* m_pRenderInterface; // 0x4
};

TOSHI_NAMESPACE_END