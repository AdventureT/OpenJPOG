#pragma once
#include "Defines.h"
#include "TKernel/TObject.h"
#include "TKernel/TPCString.h"

TOSHI_NAMESPACE_BEGIN

class TGUIINTERFACE_EXPORTS TGUITextureSection : public TObject
{
	DECLARE_DYNAMIC(TGUITextureSection)
public:
	enum Flags
	{
		TEXTURESECTIONFLAG_WRAP    = BITFIELD(0),
		TEXTURESECTIONFLAG_MIRRORX = BITFIELD(1),
		TEXTURESECTIONFLAG_MIRRORY = BITFIELD(2)
	};

public:
	TGUITextureSection();

public:
	virtual void GetBBox(TUSHORT &a_usX, TUSHORT &a_usY, TUSHORT &a_usWidth, TUSHORT &a_usHeight, TINT) const;
	virtual void GetBBox(TUSHORT &a_usX, TUSHORT &a_usY, TUSHORT &a_usWidth, TUSHORT &a_usHeight, TFLOAT) const;

public:
	// $TGUIInterface: FUNCTION 10009f90
	TSHORT GetTexture() const
	{
		return m_uTexture;
	}
	// $TGUIInterface: FUNCTION 10009f80
	const TPCString &GetName() const
	{
		return m_sName;
	}
	// $TGUIInterface: FUNCTION 10009f50
	TUSHORT GetWidth() const
	{
		return m_usWidth;
	}
	// $TGUIInterface: FUNCTION 10009f40
	TUSHORT GetHeight() const
	{
		return m_usHeight;
	}
	// $TGUIInterface: FUNCTION 10009f30
	TBOOL GetRotation() const
	{
		return m_eFlags & (TEXTURESECTIONFLAG_WRAP | TEXTURESECTIONFLAG_MIRRORX);
	}
	// $TGUIInterface: FUNCTION 10009f20
	TBOOL GetWrap() const
	{
		return (m_eFlags & TEXTURESECTIONFLAG_WRAP) != 0;
	}
	// $TGUIInterface: FUNCTION 10009f00
	TBOOL GetMirrorX() const
	{
		return (m_eFlags & TEXTURESECTIONFLAG_MIRRORX) != 0;
	}
	// $TGUIInterface: FUNCTION 10009ee0
	TBOOL GetMirrorY() const
	{
		return (m_eFlags & TEXTURESECTIONFLAG_MIRRORY) != 0;
	}

private:
	TSHORT    m_uTexture; // 0x10
	TPCString m_sName;    // 0x14
	TUSHORT   m_usX;      // 0x18
	TUSHORT   m_usY;      // 0x1A
	TUSHORT   m_usWidth;  // 0x1C
	TUSHORT   m_usHeight; // 0x1E
	Flags     m_eFlags;   // 0x20
};

TOSHI_NAMESPACE_END
