#pragma once
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TRefCounted
{
public:

	TINT DecRefCount(TPVOID)
	{
		return --m_iRefCount;
	}

	TINT GetRefCount() const
	{
		return m_iRefCount;
	}

	TINT IncRefCount(TPVOID)
	{
		return ++m_iRefCount;
	}

private:

	TRefCounted& operator=(const TRefCounted& a_rRefCounted)
	{
		return *this;
	}

	TRefCounted(const TRefCounted& a_rRefCounted)
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