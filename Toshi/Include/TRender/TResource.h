#pragma once
#include "TKernel/TObject.h"
#include "TKernel/TNodeTree.h"
#include "Defines.h"

#define MAXNAMELEN 15

TOSHI_NAMESPACE_BEGIN

class TRenderInterface;

class TRENDERINTERFACE_EXPORTS TResource
	: public TObject
	, public TNodeTree<TResource>::TNode
{
	DECLARE_DYNAMIC(TResource)

public:
	using t_RecurseCb = TBOOL (*)(TResource *a_pResource, void *a_pUserData);

	enum FLAGS
	{
		FLAGS_VALID       = BITFIELD(0),
		FLAGS_CREATED     = BITFIELD(1),
		FLAGS_DYING       = BITFIELD(2),
		FLAGS_EXTERNAL    = BITFIELD(3),
		FLAGS_DEAD        = BITFIELD(4),
		FLAGS_SCENEOBJECT = BITFIELD(5),
	};

public:
	TResource();

	virtual ~TResource();
	virtual TBOOL Create();
	virtual TBOOL Validate();
	virtual void  Invalidate();
	virtual void  DestroyResource();
	virtual void  OnDestroy();

	void SetParent(TResource *a_pParent);
	void SetName(TPCCHAR a_strName);

	void RecurseSimple(t_RecurseCb a_pfnCallback, TResource *a_pResource, TPVOID a_pUserData);

	TBOOL IsCreated() const { return m_Flags & FLAGS_CREATED; }
	TBOOL IsDying() const { return m_Flags & FLAGS_DYING; }
	TBOOL IsSceneObject() const { return m_Flags & FLAGS_SCENEOBJECT; }
	TBOOL IsDead() const { return m_Flags & FLAGS_DEAD; }
	TBOOL IsValid() const { return IsCreated() && m_Flags & FLAGS_VALID; }

	TUINT             GetUId() const { return m_uiUId; }
	TPCCHAR           GetName() const { return m_szName; }
	TRenderInterface *GetRenderer() const { return m_pRenderer; }

public:
	TRenderInterface *m_pRenderer;          // 0x18
	TCHAR             m_szName[MAXNAMELEN]; // 0x1C
	TINT8             m_Flags;              // 0x2B
	TUINT             m_uiUId;              // 0x2C
};

TOSHI_NAMESPACE_END
