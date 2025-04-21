#include "TResource.h"
#include "TSystemTools.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TResource, TObject)

static TINT s_iResourceCount    = 0;
static TINT s_iResourcesCreated = 0;

TResource::TResource()
{
	m_Flags     = 0;
	m_uiUId     = 0;
	m_pRenderer = TNULL;
	*m_szName   = 0;
	s_iResourceCount++;
	if (s_iResourcesCreated < s_iResourceCount) {
		s_iResourcesCreated = s_iResourceCount;
	}
}

TResource::~TResource()
{
	TASSERT(0 == (m_Flags & FLAGS_DEAD));
	m_Flags |= FLAGS_DEAD;
	s_iResourceCount--;
}

TBOOL TResource::Create()
{
	TASSERT(TFALSE == IsCreated());
	m_Flags |= FLAGS_CREATED;
	return TTRUE;
}

TBOOL TResource::Validate()
{
	TASSERT((TNULL == Parent()) || (TFALSE == Parent()->IsDying()));
	TASSERT(!(m_Flags & TResource::FLAGS_DYING));
	if (IsDying()) return TFALSE;
	m_Flags |= FLAGS_VALID;
	return TTRUE;
}

void TResource::Invalidate()
{
}

void TResource::DestroyResource()
{
}

void TResource::OnDestroy()
{
}

void TResource::SetParent(TResource *a_pParent)
{
	TASSERT((TNULL == a_pParent) || (TTRUE == IsDying()) || (TFALSE == a_pParent->IsDying()));
	TASSERT(TNULL != GetTree());

	GetTree()->Remove(this, TFALSE);

	if (!a_pParent) {
		GetTree()->InsertAtRoot(this);
	}
	else {
		GetTree()->Insert(a_pParent, this);
	}
}

void TResource::SetName(TPCCHAR a_strName)
{
	if (!a_strName) {
		char szName[12];
		a_strName = szName;
		szName[0] = 'r';
		szName[1] = 'e';
		szName[2] = 's';
		szName[3] = ':';
		TSystem::StringIntToString(GetUId(), &szName[4], 10);
	}
	TASSERT(TSystem::StringLength(a_strName) <= MAXNAMELEN);
	TSystem::StringCopy(m_szName, a_strName, -1);
}

TBOOL Recurse(TResource::t_RecurseCb a_pCallback, TResource *a_pResource, TBOOL a_bFlag, TPVOID a_pUserData)
{
	TResource *pResource = a_pResource;

	while (pResource) {
		TResource *pNext = pResource->Next();

		if (pNext == a_pResource || pNext == pResource || !a_bFlag) {
			pNext = TNULL;
		}

		if (!a_pCallback(pResource, a_pUserData)) {
			return TFALSE;
		}

		auto pAttached = pResource->Child();
		if (pAttached && !Recurse(a_pCallback, pResource, TTRUE, a_pUserData)) {
			return TFALSE;
		}

		pResource = pNext;
	}

	return TTRUE;
}

void TResource::RecurseSimple(t_RecurseCb a_pfnCallback, TResource *a_pResource, TPVOID a_pUserData)
{
	TASSERT(TNULL != GetTree());
	TASSERT(TNULL != a_pfnCallback);
	if (a_pResource) {
		Recurse(a_pfnCallback, a_pResource, TFALSE, a_pUserData);
	}
	else {
		Recurse(a_pfnCallback, Child(), TTRUE, a_pUserData);
	}
}
