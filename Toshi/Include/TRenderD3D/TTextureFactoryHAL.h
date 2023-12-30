#pragma once

#include "TRender/TResource.h"
#include "TRender/TTextureResource.h"

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TTextureFactoryHAL
{
public:

	virtual TTextureResource* CreateEx(TPVOID);

};

TOSHI_NAMESPACE_END