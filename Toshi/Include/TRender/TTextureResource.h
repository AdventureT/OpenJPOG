#pragma once

#include "TKernel/TDebug.h"
#include "TTextureFactory.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TTextureResource
{

	friend class TTextureFactory;

public:

	TTextureFactory::NameEntry* GetNameEntry() { return m_pNameEntry; }

private:
	TTextureFactory::NameEntry* m_pNameEntry;
};

TOSHI_NAMESPACE_END