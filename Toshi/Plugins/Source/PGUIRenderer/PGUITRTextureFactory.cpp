#include "PGuiRenderer/PGUITRTextureFactory.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

IMPLEMENT_DYNCREATE(PGUITRTextureFactory, Toshi::TGUITextureFactory);

void PGUITRTextureFactory::Create(PGUITRDisplayContext *a_pDisplayContext)
{
	m_pDisplayContext = a_pDisplayContext;
}

short PGUITRTextureFactory::ReserveTextureID(const Toshi::TPCString &a_rTextureName)
{
	return 0;
}
