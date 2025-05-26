#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TRefCounted
{
public:
	// $TKernelInterface: FUNCTION 10007ca0
	TINT DecRefCount(TPVOID a_pData = TNULL)
	{
		return --m_iRefCount;
	}

	// $TKernelInterface: FUNCTION 10007ce0
	TINT GetRefCount() const
	{
		return m_iRefCount;
	}

	// $TKernelInterface: FUNCTION 10007cb0
	TINT IncRefCount(TPVOID a_pData = TNULL)
	{
		return ++m_iRefCount;
	}

private:
	// $TKernelInterface: FUNCTION 10007c80
	TRefCounted &operator=(const TRefCounted &a_rRefCounted)
	{
		return *this;
	}

	TRefCounted(const TRefCounted &a_rRefCounted)
	{
		m_iRefCount = 0;
	}

public:
	TRefCounted()
	{
		m_iRefCount = 0;
	}

private:
	TINT m_iRefCount;
};

TOSHI_NAMESPACE_END
