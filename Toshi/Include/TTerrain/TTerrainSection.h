#pragma once
#include "TMath.h"
#include "TDebug.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TTERRAININTERFACE_EXPORTS TTerrainSection
{

public:
#define CLIPFLAG_GRASS   0x100
#define CLIPFLAG_DIRTY   0x200
#define CLIPFLAG_UNK     0x400
#define USERBITSFLAGMASK -(0x400)

	void ComputeBounds();

	// $TTerrainInterface: FUNCTION 10007cb0
	void SetDirty(bool a_bEnable)
	{
		a_bEnable ? SetSystemFlags(m_ui32ClipFlags | CLIPFLAG_DIRTY) : SetSystemFlags(m_ui32ClipFlags & ~CLIPFLAG_DIRTY);
	}
	// $TTerrainInterface: FUNCTION 1000de20
	TBOOL HasGrass()
	{
		return HASFLAG(m_ui32ClipFlags & CLIPFLAG_GRASS);
	}
	// $TTerrainInterface: FUNCTION 1000de40
	void SetGrass(bool a_bEnable)
	{
		a_bEnable ? AddFlags(CLIPFLAG_GRASS) : SetFlags(m_ui32ClipFlags & ~CLIPFLAG_GRASS);
	}
	// $TTerrainInterface: FUNCTION 1000de00
	void AddFlags(TUINT a_ui32ClipFlags)
	{
		m_ui32ClipFlags |= a_ui32ClipFlags;
	}
	// $TTerrainInterface: FUNCTION 1000de10
	void SetFlags(TUINT a_ui32ClipFlags)
	{
		m_ui32ClipFlags = a_ui32ClipFlags;
	}
	// $TTerrainInterface: FUNCTION 100069e0
	TUINT GetFlags() const
	{
		return m_ui32ClipFlags;
	}
	// $TTerrainInterface: FUNCTION 100069c0
	TTerrainSection *NextSection() const
	{
		return m_pNextSection;
	}

private:
	void SetSystemFlags(TUINT a_ui32ClipFlags);

private:
	TTerrainSection *m_pNextSection;  // 0x14
	TUINT            m_ui32ClipFlags; // 0x1C
	TUINT            m_uiTimeStamp;   // 0x20
	TCHAR            m_cBoundX;       // 0x30
	TCHAR            m_cBoundY;       // 0x31
	TCHAR            m_cPosX;         // 0x32
	TCHAR            m_cPosY;         // 0x33
};

TOSHI_NAMESPACE_END
