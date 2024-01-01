#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TNodeTree.h"
#include "Defines.h"

#define MAXNAMELEN 15

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;

class TRENDERINTERFACE_EXPORTS TResource : public TObject, public TNodeTree<TResource>::TNode
{
	DECLARE_DYNAMIC(TResource)

	enum FLAGS
	{
		FLAGS_VALID = BITFIELD(0),
		FLAGS_CREATED = BITFIELD(1),
		FLAGS_DYING = BITFIELD(2),
		FLAGS_EXTERNAL = BITFIELD(3),
		FLAGS_DEAD = BITFIELD(4),
		FLAGS_SCENEOBJECT = BITFIELD(5),
	};

public:
	
	TResource()
	{
		m_pRenderer = TNULL;
		*m_szName = 0;
		m_Flags = 0;
		m_uiUId = 0;
	}

	virtual TBOOL Create();
	virtual TBOOL Validate();

	void SetParent(TResource *a_pParent);
	void SetName(TPCCHAR a_strName);

	TBOOL IsDying() { return HASFLAG(m_Flags & FLAGS_DYING); }
	TBOOL IsCreated() { return HASFLAG(m_Flags & FLAGS_CREATED); }

	TUINT GetUId() const { return m_uiUId; }
	TPCCHAR GetName() const { return m_szName; }
	TRenderInterface* GetRenderer() const { return m_pRenderer; }

public:
	TRenderInterface* m_pRenderer;    // 0x18
	TCHAR m_szName[MAXNAMELEN];       // 0x1C
	TINT8 m_Flags;                   // 0x2B
	TUINT m_uiUId;                    // 0x2C
};

TOSHI_NAMESPACE_END