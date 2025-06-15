#pragma once
#include "PGUIRenderer/PGUITRTextureFactory.h"

class AGUITextureFactory : public PGUITRTextureFactory
{
	DECLARE_DYNAMIC(AGUISystem)

public:
	virtual Toshi::TTextureResource *LoadTTexture(const Toshi::TPCString &a_sFileName, int &a_iWidth, int &a_iHeight);
};
