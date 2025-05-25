#include "TTerrainSection.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

// $TTerrainInterface: FUNCTION 10008900
void TTerrainSection::SetSystemFlags(TUINT a_ui32ClipFlags)
{
	const TUINT uiUserBitsFlagMask = USERBITSFLAGMASK;
	TASSERT((a_ui32ClipFlags & uiUserBitsFlagMask) == 0 || (a_ui32ClipFlags & uiUserBitsFlagMask) == (m_ui32ClipFlags & uiUserBitsFlagMask));
	m_ui32ClipFlags = (m_ui32ClipFlags | CLIPFLAG_UNK - 1) & (a_ui32ClipFlags | uiUserBitsFlagMask);
}

TOSHI_NAMESPACE_END
