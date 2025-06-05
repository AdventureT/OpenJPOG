#include "TGUITextureSection.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNCREATE(TGUITextureSection, TObject);

TGUITextureSection::TGUITextureSection()
{

}

void TGUITextureSection::GetBBox(TUSHORT &a_usX, TUSHORT &a_usY, TUSHORT &a_usWidth, TUSHORT &a_usHeight, TINT) const
{
	a_usX      = m_usX;
	a_usY      = m_usY;
	a_usWidth  = m_usWidth;
	a_usHeight = m_usHeight;
}

void TGUITextureSection::GetBBox(TUSHORT &a_usX, TUSHORT &a_usY, TUSHORT &a_usWidth, TUSHORT &a_usHeight, TFLOAT) const
{
	a_usX  = m_usX;
	a_usY  = m_usY;
	a_usWidth = m_usWidth;
	a_usHeight = m_usHeight;
}

TOSHI_NAMESPACE_END