#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TNodeTree.h"

#define MAXNAMELEN 15

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;

class TOSHI_EXPORT TResource : public TObject, public TNodeTree<TResource>::TNode
{
	DECLARE_DYNAMIC(TResource)

	enum TResourceState
	{
		TResourceState_Valid = BITFIELD(0),
		TResourceState_Created = BITFIELD(1),
		TResourceState_Dying = BITFIELD(2),
		TResourceState_External = BITFIELD(3),
		TResourceState_Dead = BITFIELD(4),
		TResourceState_SceneObject = BITFIELD(5),
	};

public:
	
	TResource()
	{
		m_pRenderer = TNULL;
		*m_szName = 0;
		m_iState = 0;
		m_uiUId = 0;
	}

	virtual TBOOL Create();

	void SetParent(TResource *a_pParent);
	void SetName(TPCCHAR a_strName);

	TBOOL IsDying() { return HASFLAG(m_iState & TResourceState_Dying); }
	TBOOL IsCreated() { return HASFLAG(m_iState & TResourceState_Created); }

	TUINT GetUId() const { return m_uiUId; }
	TPCCHAR GetName() const { return m_szName; }

public:
	TRenderInterface* m_pRenderer;    // 0x18
	TCHAR m_szName[MAXNAMELEN];       // 0x1C
	TINT8 m_iState;                   // 0x2B
	TUINT m_uiUId;                    // 0x2C
};

TOSHI_NAMESPACE_END