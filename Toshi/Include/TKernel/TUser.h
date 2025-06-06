#pragma once

#include "TDebug.h"

#define MAX_USERS 50

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TUser
{
	friend class TUserHandler;

public:
	TUser(TCHAR const *a_sName);

	// $TKernelInterface: FUNCTION 1000c760
	TBOOL  IsRegistered() { return m_iUserID != -1; }
	TSHORT Register();
	void   Deregister();

	// $TKernelInterface: FUNCTION 1000c730
	TSHORT       GetUserID() { return m_iUserID; }
	// $TKernelInterface: FUNCTION 1000c740
	TSHORT       GetNameLength() { return m_iNameLen; }
	// $TKernelInterface: FUNCTION 1000c750
	TCHAR const *GetName() { return m_sName; }

private:
	TCHAR const *m_sName;    // 0x0
	TSHORT       m_iNameLen; // 0x4
	TSHORT       m_iUserID;  // 0x6
};

class TKERNELINTERFACE_EXPORTS TUserHandler
{
protected:
	TUserHandler();
	~TUserHandler() = default;

public:
	TSHORT RegisterUser(TUser &a_rUser);
	void   DeregisterUser(TUser &a_rUser);
	TUser *FindUser(TCHAR const *a_sName);

	// $TKernelInterface: FUNCTION 1000c7b0
	TINT                           GetUserCount() { return m_iUserCount; }
	// $TKernelInterface: FUNCTION 1000c7a0
	TUser                         *GetUser(TINT a_iUserID) { return m_pUsers[a_iUserID]; }
	static TUserHandler &TOSHI_API GetSingleton();

private:
	static TUserHandler ms_oSingleton;

	TINT   m_iUserCount;        // 0x0
	TUser *m_pUsers[MAX_USERS]; // 0x4
};

TOSHI_NAMESPACE_END
