#pragma once

#include "TKernel/TTask.h"
#include "TKernel/TCString.h"

class ARootTask : public Toshi::TTask
{
	DECLARE_DYNAMIC(ARootTask);
public:
	ARootTask() = default;
	virtual ~ARootTask() = default;

	void SetName(TPCHAR a_szName)
	{
		m_szName = a_szName;
	}

private:
	Toshi::TCString m_szName;
};