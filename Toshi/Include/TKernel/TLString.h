#pragma once

#include "TDebug.h"
#include "TFreeList.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TLocale
{
public:
	static int const TEMP_START_INDEX = 0x40000000;
};

class TOSHI_EXPORT TLocalisedString
{
public:
	static TFreeList& TOSHI_API GetFreeList() { return m_oFreelist; }

private:
	static TFreeList m_oFreelist;
	
	TINT m_iIDInt; // 0x4
};

TOSHI_NAMESPACE_END