#pragma once
#include "Defines.h"
#include "TCString.h"
#include <new>
TOSHI_NAMESPACE_BEGIN

// TClassProps definitions
typedef class TObject* (TOSHI_API*t_CreateTObject)();
typedef class TObject* (TOSHI_API*t_CreateTObjectInPlace)(TPVOID);
typedef void  (TOSHI_API*t_InitializeStatic)();
typedef void  (TOSHI_API*t_UninitializeStatic)();

// RecurseTree definitions
typedef TBOOL (*t_RecurceTreeCheck)(class TClass*, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseBeginCb)(class TClass*, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseEndCb)(class TClass*, TPCVOID);

#define TGetClass(X) X::m_sClass

class TOSHI_EXPORT TClass
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
	static void TOSHI_API DumpObjectClassTree();
	static const TClass* TOSHI_API Find(TPCCHAR a_pcClassName, const TClass* a_pClass);
	static const TClass* TOSHI_API FindCommonBaseClass(const TClass& a_rClass, const TClass& a_rBaseClass);
	static const TClass* TOSHI_API FindRecurse(TPCCHAR a_pcClassName, const TClass* a_pClass, TBOOL a_bHasPrevious);

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
		m_pPrevious = a_rClass.m_pPrevious;
		m_pLastAttached = a_rClass.m_pLastAttached;
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

#define DECLARE_DYNAMIC(class_name) \
public: \
	virtual Toshi::TClass& GetClass() const;                \
	static Toshi::TClass m_sClass;                          \
private: \
	static Toshi::TObject* TOSHI_API CreateObject();        \
	static Toshi::TObject* TOSHI_API CreateObjectInPlace(TPVOID a_pMem); \
	static void TOSHI_API DeinitialiseStatic();      \
	static void TOSHI_API InitialiseStatic();      

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, pfnCreateObject, pfnCreateObjectInPlace, version) \
	Toshi::TClass& class_name::GetClass() const \
		{ return class_name::m_sClass; } \
	void TOSHI_API class_name::DeinitialiseStatic() \
		{  } \
	void TOSHI_API class_name::InitialiseStatic() \
		{  } \
	Toshi::TClass class_name::m_sClass = { \
		#class_name, &TGetClass(base_class_name), pfnCreateObject, pfnCreateObjectInPlace, \
			class_name::InitialiseStatic, class_name::DeinitialiseStatic, version }; \

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	Toshi::TObject* TOSHI_API class_name::CreateObject() \
		{ return new class_name; } \
	Toshi::TObject* TOSHI_API class_name::CreateObjectInPlace(TPVOID a_pMem) \
		{ return new (a_pMem) class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, class_name::CreateObject, class_name::CreateObjectInPlace, 1)

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	Toshi::TObject* TOSHI_API class_name::CreateObject() \
		{ TASSERT(!"This class does not support dynamic creation!"); return TNULL; } \
	Toshi::TObject* TOSHI_API class_name::CreateObjectInPlace(TPVOID a_pMem) \
		{ TASSERT(!"This class does not support dynamic creation!"); return TNULL; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, class_name::CreateObject, class_name::CreateObjectInPlace, 1)

class TOSHI_EXPORT TObject
{	
private: 
	static TObject* TOSHI_API CreateObject()
	{
		return new TObject;
	}
	static TObject* TOSHI_API CreateObjectInPlace(TPVOID a_pMem)
	{
		return new (a_pMem) TObject;
	}
	static void TOSHI_API DeinitialiseStatic() {}
	static void TOSHI_API InitialiseStatic() {}
	
public:
	virtual void Delete() { delete this; }

	TBOOL IsA(const TClass& a_rClass) const { return GetClass().IsA(a_rClass); }
	TBOOL IsExactly(const TClass& a_rClass) const { return GetClass().IsExactly(a_rClass); }

	virtual TClass& GetClass() const { return m_sClass; }
	inline static TClass m_sClass = TClass("TObject", TNULL, TObject::CreateObject, TObject::CreateObjectInPlace, TObject::InitialiseStatic, TObject::DeinitialiseStatic, 1);

protected:
	TObject() {}
	virtual ~TObject() = default;

};

TOSHI_NAMESPACE_END