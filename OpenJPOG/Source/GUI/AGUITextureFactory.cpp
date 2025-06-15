#include "AGUITextureFactory.h"

IMPLEMENT_DYNCREATE(AGUITextureFactory, PGUITRTextureFactory)

Toshi::TTextureResource *AGUITextureFactory::LoadTTexture(const Toshi::TPCString &a_sFileName, int &a_iWidth, int &a_iHeight)
{
	return PGUITRTextureFactory::LoadTTexture(a_sFileName, a_iWidth, a_iHeight);
}