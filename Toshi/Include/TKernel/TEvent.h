#pragma once
#include "TDList.h"

TOSHI_NAMESPACE_BEGIN

class TGenericEmitter;

class TKERNELINTERFACE_EXPORTS TGenericListener : public TPriList<TGenericListener>::TNode
{
public:
	using t_Callback = TBOOL (*)(void *a_pCaller, void *a_pOwner, void *a_pData);
	friend class TGenericEmitter;

public:
	TGenericListener()
	{
		m_pCaller   = TNULL;
		m_pCallback = TNULL;
	}
	TGenericListener(TGenericEmitter *a_pEmitter, void *a_pCaller, t_Callback a_pCallback, int a_iPriority)
	{
		Connect(a_pEmitter, a_pCaller, a_pCallback, a_iPriority);
	}
	// $TKernelInterface: FUNCTION 1000cd10
	~TGenericListener()
	{
		Disconnect();
	}

	void Connect(TGenericEmitter *a_pEmitter, void *a_pCaller, t_Callback a_pCallback, int a_iPriority);
	void Disconnect();

private:
	void      *m_pCaller;
	t_Callback m_pCallback;
};

class TKERNELINTERFACE_EXPORTS TGenericEmitter
{
public:
	friend class TGenericListener;

	TGenericEmitter()
	{
		Create(TNULL);
	}

	TGenericEmitter(void *a_pOwner)
	{
		Create(a_pOwner);
	}

	// $TKernelInterface: FUNCTION 1000cd90
	~TGenericEmitter()
	{
		Destroy();
	}

	// $TKernelInterface: FUNCTION 1000cc50
	void Throw(void *a_pData)
	{
		for (auto it = m_Listeners.Begin(); it != m_Listeners.End(); it++) {
			it->m_pCallback(it->m_pCaller, m_pOwner, a_pData);
		}
	}

	// $TKernelInterface: FUNCTION 1000cd80
	void Create(void *a_pOwner)
	{
		m_pOwner = a_pOwner;
	}

	// $TKernelInterface: FUNCTION 1000cc20
	void Destroy()
	{
		for (auto it = m_Listeners.Begin(); it != m_Listeners.End(); it++) {
			it->Disconnect();
		}

		m_pOwner = TNULL;
	}

private:
	TPriList<TGenericListener> m_Listeners;
	void                      *m_pOwner;
};

template <typename Owner, typename Data = Owner>
class TEmitter : public TGenericEmitter
{
public:
	TEmitter() = default;
	TEmitter(Owner *owner)
		: TGenericEmitter(owner) {}

	void Throw(Data *pData) { TGenericEmitter::Throw(pData); }
	void Throw(Data &&data) { TGenericEmitter::Throw(&data); }

	void Create(Owner *owner) { TGenericEmitter::Create(owner); }
	void Destroy() { TGenericEmitter::Destroy(); }

	TEmitter(const TEmitter &) = delete;
	TEmitter(TEmitter &&)      = delete;
};

template <typename Owner, typename Data, typename Caller>
class TListener : public TGenericListener
{
public:
	using t_CallerCallback = TBOOL (*)(Caller *a_pCaller, Owner *a_pOwner, Data *a_pData);

public:
	void Connect(TGenericEmitter *a_rEmitter, Caller *a_pCaller, t_CallerCallback a_pCallback, int a_iPriority)
	{
		TGenericListener::Connect(
			a_rEmitter,
			a_pCaller,
			(t_Callback)a_pCallback,
			a_iPriority);
	}
};

class TKERNELINTERFACE_EXPORTS TNullEvent
{

};

TOSHI_NAMESPACE_END
