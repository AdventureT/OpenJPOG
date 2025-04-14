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

	void SetDirty(bool a_bEnable)
	{
		a_bEnable ? SetSystemFlags(m_ui32ClipFlags | CLIPFLAG_DIRTY) : SetSystemFlags(m_ui32ClipFlags & ~CLIPFLAG_DIRTY);
	}
	TBOOL HasGrass()
	{
		return HASFLAG(m_ui32ClipFlags & CLIPFLAG_GRASS);
	}
	void SetGrass(bool a_bEnable)
	{
		a_bEnable ? AddFlags(CLIPFLAG_GRASS) : SetFlags(m_ui32ClipFlags & ~CLIPFLAG_GRASS);
	}
	void AddFlags(TUINT a_ui32ClipFlags)
	{
		m_ui32ClipFlags |= a_ui32ClipFlags;
	}
	void SetFlags(TUINT a_ui32ClipFlags)
	{
		m_ui32ClipFlags = a_ui32ClipFlags;
	}
	TUINT GetFlags() const
	{
		return m_ui32ClipFlags;
	}
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
