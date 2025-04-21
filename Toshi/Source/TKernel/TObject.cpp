#include "TObject.h"
#include "TSystemTools.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

TClass::TClass(TPCCHAR a_pcName, TClass *a_pParent, t_CreateTObject a_Create, t_CreateTObjectInPlace a_CreateInPlace, t_InitializeStatic a_Init, t_UninitializeStatic a_Uninit, TUINT a_uiVersion)
{
	m_pcName        = a_pcName;
	m_Create        = a_Create;
	m_CreateInPlace = a_CreateInPlace;
	m_Initialize    = a_Init;
	m_Uninitialize  = a_Uninit;
	m_pParent       = a_pParent;
	m_uiVersion     = a_uiVersion;
	m_bInitialised  = TFALSE;
	AttachClassToParent();
}

TClass::~TClass()
{
	DetachClassFromParent();
	m_pLastAttached = TNULL;
	m_pPrevious     = TNULL;
	m_pParent       = TNULL;
	if (m_bInitialised) {
		DeinitialiseStatic();
	}
}

void TClass::DeinitialiseStatic()
{
	if (m_Uninitialize && !m_bInitialised) {
		TASSERT(TTRUE == m_bInitialised);
		m_bInitialised = TFALSE;
		m_Uninitialize();
	}
}

static TINT  s_iCounter;
static TCHAR s_FourSpaces[4] = { ' ', ' ', ' ', ' ' };

TBOOL DumpObjectClassTree_BaseBegin(TClass *, TPCVOID)
{
	s_iCounter++;
	return TTRUE;
}

TBOOL DumpObjectClassTree_BaseEnd(TClass *, TPCVOID)
{
	s_iCounter--;
	return TTRUE;
}

TBOOL DumpObjectClassTree_Check(TClass *a_pClass, TPCVOID a_pData)
{
	for (TINT i = 0; i < s_iCounter; i++)
	{
		TCString idk;
		idk.Format("%.4s", s_FourSpaces);
		idk.Print();
	}
	TCString idk2;
	idk2.Format("%s : ver=%u.%u\n", a_pClass->GetName(), a_pClass->GetVersionMajor(), a_pClass->GetVersionMinor());
	idk2.Print();
	return TTRUE;
}

void TOSHI_API TClass::DumpObjectClassTree()
{
	s_iCounter      = 0;
	TClass *pObject = (TClass *)Find("TObject", TNULL);
	pObject->RecurseTree(DumpObjectClassTree_BaseBegin, DumpObjectClassTree_BaseEnd, DumpObjectClassTree_Check, TNULL);
}

const TClass *TOSHI_API TClass::Find(TPCCHAR a_pcClassName, const TClass *a_pClass)
{
	TASSERT(a_pcClassName[1] != 0);
	if (a_pClass == TNULL) a_pClass = &TGetClass(TObject);
	return FindRecurse(a_pcClassName, a_pClass, TFALSE);
}

const TClass *TOSHI_API TClass::FindCommonBaseClass(const TClass &a_rClass, const TClass &a_rBaseClass)
{
	return nullptr;
}

const TClass *TOSHI_API TClass::FindRecurse(TPCCHAR a_pcClassName, const TClass *a_pClass, TBOOL a_bHasPrevious)
{
	while (a_pClass) {
		TClass *pPrevious  = a_bHasPrevious ? a_pClass->m_pPrevious : TNULL;
		int     difference = TSystem::StringCompareNoCase(a_pClass->GetName(), a_pcClassName, -1);
		if (difference == 0) return a_pClass;
		if (a_pClass->m_pLastAttached) {
			const TClass *result = FindRecurse(a_pcClassName, a_pClass->m_pLastAttached, TTRUE);
			if (result) return result;
		}
		a_pClass = pPrevious;
	}
	return TNULL;
}

void TClass::InitialiseStatic()
{
	if (m_Initialize && !m_bInitialised) {
		TASSERT(TFALSE == m_bInitialised);
		m_bInitialised = TTRUE;
		m_Initialize();
	}
}

TBOOL TClass::IsA(const TClass &a_rClass) const
{
	for (const TClass *pClass = this; pClass != TNULL; pClass = pClass->m_pParent) {
		if (pClass->IsExactly(a_rClass)) return TTRUE;
	}
	return TFALSE;
}

void TClass::RecurseTree(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem)
{
	TBOOL valid = a_Check ? a_Check(this, a_pMem) : TFALSE;
	if (valid) {
		if (a_BaseBegin) a_BaseBegin(this, a_pMem);
		RecurseTree2(a_BaseBegin, a_BaseEnd, a_Check, a_pMem);
		if (a_BaseEnd) a_BaseEnd(this, a_pMem);
	}
}

void TClass::RecurseTree2(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem)
{
	for (TClass *pClass = m_pLastAttached; pClass != TNULL; pClass = pClass->m_pPrevious) {
		if (a_Check) a_Check(pClass, a_pMem);
		if (pClass->m_pLastAttached) {
			if (a_BaseBegin) a_BaseBegin(pClass, a_pMem);
			pClass->RecurseTree2(a_BaseBegin, a_BaseEnd, a_Check, a_pMem);
			if (a_BaseEnd) a_BaseEnd(pClass, a_pMem);
		}
	}
}

TBOOL TClass::AttachClassToParent()
{
	if (m_pParent && !IsAttached()) {
		m_pPrevious                = m_pParent->m_pLastAttached;
		m_pParent->m_pLastAttached = this;
		return TTRUE;
	}
	return TFALSE;
}

TBOOL TClass::IsAttached() const
{
	if (m_pParent) {
		for (TClass *i = m_pParent->m_pLastAttached; i != TNULL; i = i->m_pPrevious) {
			if (i == this) return TTRUE;
		}
	}
	return TFALSE;
}
