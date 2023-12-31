#include "TResource.h"
#include "TSystemTools.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TResource, TObject)

TBOOL TResource::Create()
{
	TASSERT(TFALSE == IsCreated());
	m_Flags |= FLAGS_CREATED;
	return TTRUE;
}

TBOOL TResource::Validate()
{
	TASSERT((TNULL==Parent()) || (TFALSE==Parent()->IsDying()));
	TASSERT(!(m_Flags&TResource::FLAGS_DYING));
	if (IsDying()) return TFALSE;
	m_Flags |= FLAGS_VALID;
	return TTRUE;
}

void TResource::SetParent(TResource* a_pParent)
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
	TASSERT(TSystem::StringLength(a_strName)<=MAXNAMELEN);
	TSystem::StringCopy(m_szName, a_strName, -1);
}
