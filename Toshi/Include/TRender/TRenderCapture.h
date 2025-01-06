#pragma once
#include "Defines.h"
#include "TKernel/TDebug.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TRenderCapture
{
public:

	enum FORMAT
	{
		FORMAT_RGBA32,
		FORMAT_RGB24,
	};

	TRenderCapture() = default;

	virtual ~TRenderCapture() = default;
	virtual TBOOL Create(FORMAT a_eFormat, TINT a_iWidth, TINT a_iHeight) = 0;
	virtual void Destroy() = 0;
	virtual TBOOL Request() = 0;
	virtual TBOOL Wait() = 0;
	virtual TBOOL Poll() = 0;
	virtual TPVOID ObtainBuffer() = 0;
	virtual void ReleaseBuffer() = 0;
};

TOSHI_NAMESPACE_END