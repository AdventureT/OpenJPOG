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

	// $TRenderInterface: FUNCTION 10018460
	TBOOL IsCreated() const { return m_Flags & FLAGS_CREATED; }
	// $TRenderInterface: FUNCTION 10018450
	TBOOL IsDying() const { return m_Flags & FLAGS_DYING; }
	// $TRenderInterface: FUNCTION 10009890
	TBOOL IsSceneObject() const { return m_Flags & FLAGS_SCENEOBJECT; }
	TBOOL IsDead() const { return m_Flags & FLAGS_DEAD; }
	// $TRenderInterface: FUNCTION 10018470
	TBOOL IsValid() const { return IsCreated() && m_Flags & FLAGS_VALID; }

	// $TRenderInterface: FUNCTION 10018410
	TUINT             GetUId() const { return m_uiUId; }
	// $TRenderInterface: FUNCTION 10018420
	TPCCHAR           GetName() const { return m_szName; }
	// $TRenderInterface: FUNCTION 10018430
	TRenderInterface *GetRenderer() const { return m_pRenderer; }

public:
	TRenderInterface *m_pRenderer;          // 0x18
	TCHAR             m_szName[MAXNAMELEN]; // 0x1C
	TINT8             m_Flags;              // 0x2B
	TUINT             m_uiUId;              // 0x2C
};

TOSHI_NAMESPACE_END
