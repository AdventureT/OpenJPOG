#pragma once
#include "Defines.h"

#include <TKernel/TKernelInterface.h>

#ifdef TOSHI_SKU_WINDOWS
#  include <windows.h>
#endif

TOSHI_NAMESPACE_BEGIN

class TAPPLICATION_EXPORTS TApplication
{

private:
	enum TApplicationFlag
	{
		TApplicationFlag_Created   = BITFIELD(0),
		TApplicationFlag_Destroyed = BITFIELD(1),
	};

public:
	TApplication();
	virtual ~TApplication();

	TBOOL Create(TPCCHAR a_pcName, TINT argc, TPCHAR *const argv);
	TBOOL Execute();

	TBOOL IsCreated()
	{
		return HASFLAG(m_uiState & TApplicationFlag_Created);
	}

	void SetVerbose(TBOOL a_bVerbose)
	{
		m_bVerbose = a_bVerbose;
	}

	TBOOL ShowConsole(TBOOL a_bShowConsole);
	TBOOL ToggleConsole()
	{
		ShowConsole(!m_bShowConsole);
		return m_bShowConsole;
	}

	void Destroy()
	{
		m_uiState |= TApplicationFlag_Destroyed;
	}

	void DisplayErrorMessageBox(TCString a_oErrorMessage)
	{
		MessageBox(*m_hConsole, a_oErrorMessage.GetString(), "Error", 0);
	}

	virtual TBOOL OnCreate(TINT argc, TPCHAR *const argv)
	{
		m_uiState |= TApplicationFlag_Created;
		return TTRUE;
	}

	virtual TBOOL OnDestroy()
	{
		return TTRUE;
	}

	virtual TBOOL OnUpdate(TFLOAT a_fDelta)
	{
		return (m_uiState & TApplicationFlag_Destroyed) == 0;
	}

	TKernelInterface *GetKernel() { return m_pKernel; }

private:
	TKernelInterface *m_pKernel;      // 0x4
	TCString          m_pcName;       // 0x8
	TINT              m_uiState;      // 0x10
	TBOOL             m_bVerbose;     // 0x14
	TBOOL             m_bShowConsole; // 0x15
	HWND             *m_hConsole;     // 0x18
};

TOSHI_NAMESPACE_END
