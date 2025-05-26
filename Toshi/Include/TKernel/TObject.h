#pragma once
#include "Defines.h"
#include "TCString.h"
#include <new>


TOSHI_NAMESPACE_BEGIN

// TClassProps definitions
typedef class TObject *(TOSHI_API *t_CreateTObject)();
typedef class TObject *(TOSHI_API *t_CreateTObjectInPlace)(TPVOID);
typedef void(TOSHI_API *t_InitializeStatic)();
typedef void(TOSHI_API *t_UninitializeStatic)();

// RecurseTree definitions
typedef TBOOL (*t_RecurceTreeCheck)(class TClass *, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseBeginCb)(class TClass *, TPCVOID);
typedef TBOOL (*t_RecurceTreeBaseEndCb)(class TClass *, TPCVOID);

#define TGetClass(X)     X::m_sClass
#define TFindClass(X, Y) Toshi::TClass::Find(#X, Y)

class TKERNELINTERFACE_EXPORTS TClass
{
public:
	TClass(TPCCHAR a_pcName, TClass *a_pParent, t_CreateTObject a_Create, t_CreateTObjectInPlace a_CreateInPlace, t_InitializeStatic a_Init, t_UninitializeStatic a_Uninit, TUINT a_uiVersion);
	~TClass();

	// $TKernelInterface: FUNCTION 10027e00
	TObject *CreateObject() const
	{
		return m_Create ? m_Create() : TNULL;
	}

	// $TKernelInterface: FUNCTION 10027de0
	TObject *CreateObjectInPlace(TPVOID a_pMem) const
	{
		return m_CreateInPlace ? m_CreateInPlace(a_pMem) : TNULL;
	}

	void                           DeinitialiseStatic();
	// $TKernelInterface: FUNCTION 10027d50
	TBOOL                          DetachClassFromParent() { return TTRUE; }
	static void TOSHI_API          DumpObjectClassTree();
	static const TClass *TOSHI_API Find(TPCCHAR a_pcClassName, const TClass *a_pClass);
	static const TClass *TOSHI_API FindCommonBaseClass(const TClass &a_rClass, const TClass &a_rBaseClass);
	static const TClass *TOSHI_API FindRecurse(TPCCHAR a_pcClassName, const TClass *a_pClass, TBOOL a_bHasPrevious);

	// $TKernelInterface: FUNCTION 10027dc0
	TPCCHAR       GetName() const { return m_pcName; }
	// $TKernelInterface: FUNCTION 10027dd0
	const TClass *GetParent() const { return m_pParent; }
	// $TKernelInterface: FUNCTION 10027db0
	TUINT         GetVersion() const { return m_uiVersion; }
	// $TKernelInterface: FUNCTION 10027da0
	TUSHORT       GetVersionMajor() const { return m_uiVersion >> 16; }
	// $TKernelInterface: FUNCTION 10027d90
	TUSHORT       GetVersionMinor() const { return m_uiVersion & 0xFFFF; }

	void  InitialiseStatic();
	TBOOL IsA(const TClass &a_rClass) const;
	TBOOL IsAttached() const;
	// $TKernelInterface: FUNCTION 10027d70
	TBOOL IsExactly(const TClass &a_rClass) const
	{
		return *this == a_rClass;
	}
	// $TKernelInterface: FUNCTION 10027d60
	TBOOL IsStaticInitialised() const
	{
		return m_bInitialised;
	}

	// $TKernelInterface: FUNCTION 10007c30
	TClass &operator=(const TClass &a_rClass)
	{
		m_pcName        = a_rClass.m_pcName;
		m_Create        = a_rClass.m_Create;
		m_CreateInPlace = a_rClass.m_CreateInPlace;
		m_Initialize    = a_rClass.m_Initialize;
		m_Uninitialize  = a_rClass.m_Uninitialize;
		m_pParent       = a_rClass.m_pParent;
		m_pPrevious     = a_rClass.m_pPrevious;
		m_pLastAttached = a_rClass.m_pLastAttached;
		m_uiVersion     = a_rClass.m_uiVersion;
		m_bInitialised  = TFALSE;
		return *this;
	}
	// $TKernelInterface: FUNCTION 10027d00
	TBOOL operator==(const TClass &a_rClass) const
	{
		return m_pcName == a_rClass.m_pcName;
	}

	void RecurseTree(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem);
	void RecurseTree2(t_RecurceTreeBaseBeginCb a_BaseBegin, t_RecurceTreeBaseEndCb a_BaseEnd, t_RecurceTreeCheck a_Check, TPCVOID a_pMem);

	TBOOL AttachClassToParent();

private:
	TPCCHAR                m_pcName;        // 0x00
	t_CreateTObject        m_Create;        // 0x04
	t_CreateTObjectInPlace m_CreateInPlace; // 0x08
	t_InitializeStatic     m_Initialize;    // 0x0C
	t_UninitializeStatic   m_Uninitialize;  // 0x10
	TClass                *m_pParent;       // 0x14
	TClass                *m_pPrevious;     // 0x18
	TClass                *m_pLastAttached; // 0x1C
	TUINT                  m_uiVersion;     // 0x20
	TBOOL                  m_bInitialised;  // 0x24
};

#define DECLARE_DYNAMIC(class_name)                                      \
public:                                                                  \
	virtual Toshi::TClass &GetClass() const;                             \
	static Toshi::TClass   m_sClass;                                     \
                                                                         \
private:                                                                 \
	static Toshi::TObject *TOSHI_API CreateObject();                     \
	static Toshi::TObject *TOSHI_API CreateObjectInPlace(TPVOID a_pMem); \
	static void TOSHI_API            DeinitialiseStatic();               \
	static void TOSHI_API            InitialiseStatic();

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, pfnCreateObject, pfnCreateObjectInPlace, version) \
	Toshi::TClass &class_name::GetClass() const                                                               \
	{                                                                                                         \
		return class_name::m_sClass;                                                                          \
	}                                                                                                         \
	void TOSHI_API class_name::DeinitialiseStatic()                                                           \
	{}                                                                                                        \
	void TOSHI_API class_name::InitialiseStatic()                                                             \
	{}                                                                                                        \
	Toshi::TClass class_name::m_sClass = {                                                                    \
		#class_name, &TGetClass(base_class_name), pfnCreateObject, pfnCreateObjectInPlace,                    \
		class_name::InitialiseStatic, class_name::DeinitialiseStatic, version                                 \
	};

#define IMPLEMENT_DYNCREATE(class_name, base_class_name)                     \
	Toshi::TObject *TOSHI_API class_name::CreateObject()                     \
	{                                                                        \
		return new class_name;                                               \
	}                                                                        \
	Toshi::TObject *TOSHI_API class_name::CreateObjectInPlace(TPVOID a_pMem) \
	{                                                                        \
		return new (a_pMem) class_name;                                      \
	}                                                                        \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, class_name::CreateObject, class_name::CreateObjectInPlace, 1)

#define IMPLEMENT_DYNAMIC(class_name, base_class_name)                       \
	Toshi::TObject *TOSHI_API class_name::CreateObject()                     \
	{                                                                        \
		TASSERT(!"This class does not support dynamic creation!");           \
		return TNULL;                                                        \
	}                                                                        \
	Toshi::TObject *TOSHI_API class_name::CreateObjectInPlace(TPVOID a_pMem) \
	{                                                                        \
		TASSERT(!"This class does not support dynamic creation!");           \
		return TNULL;                                                        \
	}                                                                        \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, class_name::CreateObject, class_name::CreateObjectInPlace, 1)

class TKERNELINTERFACE_EXPORTS TObject
{
private:
	// $TKernelInterface: FUNCTION 10027cc0
	static TObject *TOSHI_API CreateObject()
	{
		return new TObject;
	}
	// $TKernelInterface: FUNCTION 10027ca0
	static TObject *TOSHI_API CreateObjectInPlace(TPVOID a_pMem)
	{
		return new (a_pMem) TObject;
	}
	// $TKernelInterface: FUNCTION 10027c80
	static void TOSHI_API DeinitialiseStatic() {}
	// $TKernelInterface: FUNCTION 10027c90
	static void TOSHI_API InitialiseStatic() {}

public:
	// $TKernelInterface: FUNCTION 10027c70
	virtual void Delete() { delete this; }

	// $TKernelInterface: FUNCTION 10027c50
	TBOOL IsA(const TClass &a_rClass) const { return GetClass().IsA(a_rClass); }
	// $TKernelInterface: FUNCTION 10027c30
	TBOOL IsExactly(const TClass &a_rClass) const { return GetClass().IsExactly(a_rClass); }

	// $TKernelInterface: FUNCTION 10027cf0
	virtual TClass      &GetClass() const { return m_sClass; }
	inline static TClass m_sClass = TClass("TObject", TNULL, TObject::CreateObject, TObject::CreateObjectInPlace, TObject::InitialiseStatic, TObject::DeinitialiseStatic, 1);

protected:
	// $TKernelInterface: FUNCTION 10007c20
	TObject() {}
	virtual ~TObject() = default;
};

TOSHI_NAMESPACE_END

//-----------------------------------------------------------------------------
// Safely casts TObject to specified TClass
//-----------------------------------------------------------------------------
template <class T>
TFORCEINLINE T *TDynamicCast(Toshi::TObject *a_pObject)
{
	TSTATICASSERT(T::IsTObject);

	if (a_pObject)
	{
		if (a_pObject->IsA(&TGetClass(T)))
		{
			return TSTATICCAST(T, a_pObject);
		}
	}

	return TNULL;
}

#define TDYNAMICCAST(T, OBJECT) (TDynamicCast<T>(OBJECT))
