#pragma once
#include "TKernel/TKernelInterface.h"
#include <windows.h>

TOSHI_NAMESPACE_BEGIN

class TOSHI_EXPORT TApplication
{

private:
	enum TApplicationFlag
	{
		TApplicationFlag_Created = BITFIELD(0),
		TApplicationFlag_Destroyed = BITFIELD(1),
	};

public:

	TApplication()
	{
		m_uiState = 0;
		m_bVerbose = TTRUE;
		m_bShowConsole = TTRUE;
	}

	TBOOL Create(TPCCHAR a_pcName, TINT argc, TPCCHAR* argv);
	TBOOL Execute();

	TBOOL IsCreated()
	{
		return (m_uiState & TApplicationFlag_Created) != 0;
	}

	void SetVerbose(TBOOL a_bVerbose)
	{
		m_bVerbose = a_bVerbose;
	}

	void Destroy()
	{
		m_uiState |= TApplicationFlag_Destroyed;
	}

	void DisplayErrorMessageBox(TCString a_oErrorMessage)
	{
		MessageBox(m_hError, a_oErrorMessage.GetString(), "Error", 0);
	}

	virtual TBOOL OnCreate(TINT argc, TPCCHAR* argv)
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
		return (m_uiState & TApplicationFlag_Destroyed) != 0;
	}

private:
	TKernelInterface* m_pKernel; //0x4
	TCString m_pcName;           // 0x8
	TINT m_uiState;              // 0x10
	TBOOL m_bVerbose;            // 0x14
	TBOOL m_bShowConsole;        // 0x15
	HWND m_hError;               // 0x18
};

TOSHI_NAMESPACE_END