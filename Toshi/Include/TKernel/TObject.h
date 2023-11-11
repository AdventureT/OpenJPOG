#include "Defines.h"
#include <new>
TOSHI_NAMESPACE_BEGIN

class TObject;

// TClassProps definitions
typedef class TObject* (*t_CreateTObject)();
typedef class TObject* (*t_CreateTObjectInPlace)(TPVOID);
typedef void  (*t_InitializeStatic)();
typedef void  (*t_UninitializeStatic)();

// RecurseTree definitions
typedef TBOOL (*t_RecurceTreeCheck)(class TClass*, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseBeginCb)(class TClass*, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseEndCb)(class TClass*, TPCVOID);

TOSHI_EXPORT class TClass
{
public:
	TClass(TPCCHAR a_pcName, TClass* a_pParent, t_CreateTObject a_Create, t_CreateTObjectInPlace a_CreateInPlace, t_InitializeStatic a_Init, t_UninitializeStatic a_Uninit, TUINT a_uiVersion);
	~TClass();

	TObject* CreateObject() const
	{
		return m_Create ? m_Create() : TNULL;
	}

	TObject* CreateObjectInPlace(TPVOID a_pMem) const
	{
		return m_CreateInPlace ? m_CreateInPlace(a_pMem) : TNULL;
	}

	void DeinitialiseStatic();
	TBOOL DetachClassFromParent() { return TTRUE; }
	static void __stdcall DumpObjectClassTree();
	static const TClass* __stdcall Find(TPCCHAR a_pcClassName, const TClass* a_pClass);
	static const TClass* __stdcall FindCommonBaseClass(const TClass& a_rClass, const TClass& a_rBaseClass);
	static const TClass* __stdcall FindRecurse(TPCCHAR a_pcClassName, const TClass* a_pClass, TBOOL a_bHasPrevious);

	TPCCHAR GetName() const { return m_pcName; }
	const TClass* GetParent() const { return m_pParent; }
	TUINT GetVersion() const { return m_uiVersion; }
	TUSHORT GetVersionMajor() const { return m_uiVersion >> 16; }
	TUSHORT GetVersionMinor() const { return m_uiVersion & 0xFFFF; }

	void InitialiseStatic();
	TBOOL IsA(const TClass &a_rClass) const;
	TBOOL IsAttached() const;
	TBOOL IsExactly(const TClass& a_rClass) const
	{
		return *this == a_rClass;
	}
	TBOOL IsStaticInitialised() const
	{
		return m_bInitialised;
	}

	TClass& operator=(const TClass& a_rClass)
	{
		m_pcName = a_rClass.m_pcName;
		m_Create = a_rClass.m_Create;
		m_CreateInPlace = a_rClass.m_CreateInPlace;
		m_Initialize = a_rClass.m_Initialize;
		m_Uninitialize = a_rClass.m_Uninitialize;
		m_pParent = a_rClass.m_pParent;
		m_uiVersion = a_rClass.m_uiVersion;
		m_bInitialised = TFALSE;
		return *this;
	}
	TBOOL operator==(const TClass& a_rClass) const
	{
		return m_pcName == a_rClass.m_pcName;
	}

	void RecurseTree(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem);
	void RecurseTree2(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem);

	TBOOL AttachClassToParent();

private:
	TPCCHAR m_pcName;                       // 0x00
	t_CreateTObject m_Create;               // 0x04
	t_CreateTObjectInPlace m_CreateInPlace; // 0x08
	t_InitializeStatic m_Initialize;        // 0x0C
	t_UninitializeStatic m_Uninitialize;    // 0x10
	TClass* m_pParent;                      // 0x14
	TClass* m_pPrevious;                    // 0x18
	TClass* m_pLastAttached;                // 0x1C
	TUINT m_uiVersion;                      // 0x20
	TBOOL m_bInitialised;                   // 0x24
};

class TOSHI_EXPORT TObject
{
private:
	static TObject* __stdcall CreateObject()
	{
		TObject* pObject = new TObject();
		return pObject ? pObject : TNULL;
	}
	static TObject* __stdcall CreateObjectInPlace(TPVOID m_pMem)
	{
		TObject* pObject = new (m_pMem) TObject();
		return pObject ? pObject : TNULL;
	}
public:
	//static TClass m_sClass;
};

TOSHI_NAMESPACE_END