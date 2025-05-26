#pragma once

#include "TDebug.h"
#include "TFreeList.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TLString
{
};

class TKERNELINTERFACE_EXPORTS TLocale
{
public:
	static int const TEMP_START_INDEX = 0x40000000;
};

class TKERNELINTERFACE_EXPORTS TLocalisedString
{
public:
	// $TKernelInterface: FUNCTION 1001f300
	static TFreeList &TOSHI_API GetFreeList() { return m_oFreelist; }

private:
	static TFreeList m_oFreelist;

	TINT m_iIDInt; // 0x4
};

TOSHI_NAMESPACE_END
