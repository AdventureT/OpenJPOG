#include "TUser.h"
#include "TSystemTools.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

TUserHandler TUserHandler::ms_oSingleton = TUserHandler();

TUser::TUser(TCHAR const *a_sName)
{
	m_sName   = a_sName;
	m_iUserID = -1;
	TVALIDADDRESS(m_sName);
	m_iNameLen = TSystem::StringLength(m_sName);
}

TUserHandler::TUserHandler()
{
	m_iUserCount = 0;
	TSystem::MemSet(m_pUsers, 0, sizeof(m_pUsers));
}

TSHORT TUserHandler::RegisterUser(TUser &a_rUser)
{
	TASSERT(TFALSE == a_rUser.IsRegistered());
	TINT curUserCount = GetUserCount();
	if (curUserCount < MAX_USERS) {
		m_iUserCount++;
		a_rUser.m_iUserID      = curUserCount;
		m_pUsers[curUserCount] = &a_rUser;
		return a_rUser.GetUserID();
	}
	a_rUser.m_iUserID = -1;
	return -1;
}

void TUserHandler::DeregisterUser(TUser &a_rUser)
{
	if (a_rUser.GetUserID() != -1) {
		m_pUsers[a_rUser.GetUserID()] = TNULL;
	}
	a_rUser.m_iUserID = -1;
}

TUser *TUserHandler::FindUser(TCHAR const *a_sName)
{
	TINT iNameLength = TSystem::StringLength(a_sName);
	for (TINT i = 0; i < MAX_USERS; i++) {
		if (m_pUsers[i] &&
		    m_pUsers[i]->GetNameLength() == iNameLength &&
		    TSystem::StringCompareNoCase(m_pUsers[i]->GetName(), a_sName, -1) == 0) {
			return m_pUsers[i];
		}
	}
	return TNULL;
}

TUserHandler &TUserHandler::GetSingleton()
{
	return ms_oSingleton;
}

TSHORT TUser::Register()
{
	return TUserHandler::GetSingleton().RegisterUser(*this);
}

void TUser::Deregister()
{
	TUserHandler::GetSingleton().DeregisterUser(*this);
}
