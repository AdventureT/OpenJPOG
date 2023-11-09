#pragma once
#include "Defines.h"

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
	TBOOL Create(TPCCHAR a_pcName, TINT a_unk, TPCCHAR* a_ppcUnk2);

	void Destroy()
	{
		m_uiState |= TApplicationFlag_Destroyed;
	}

private:
	TINT m_uiState;
};

TOSHI_NAMESPACE_END