#pragma once
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TMatrix44
{
public:

	TMatrix44() = default;

	TMatrix44(
		TFLOAT a_f11,
		TFLOAT a_f12,
		TFLOAT a_f13,
		TFLOAT a_f14,
		TFLOAT a_f21,
		TFLOAT a_f22,
		TFLOAT a_f23,
		TFLOAT a_f24,
		TFLOAT a_f31,
		TFLOAT a_f32,
		TFLOAT a_f33,
		TFLOAT a_f34,
		TFLOAT a_f41,
		TFLOAT a_f42,
		TFLOAT a_f43,
		TFLOAT a_f44)
		: m_f11(a_f11), m_f12(a_f12), m_f13(a_f13), m_f14(a_f14), m_f21(a_f21), m_f22(a_f22), m_f23(a_f23), m_f24(a_f24), m_f31(a_f31), m_f32(a_f32), m_f33(a_f33), m_f34(a_f34), m_f41(a_f41), m_f42(a_f42), m_f43(a_f43), m_f44(a_f44)
	{}

	void Set(
		TFLOAT a_f11,
		TFLOAT a_f12,
		TFLOAT a_f13,
		TFLOAT a_f14,
		TFLOAT a_f21,
		TFLOAT a_f22,
		TFLOAT a_f23,
		TFLOAT a_f24,
		TFLOAT a_f31,
		TFLOAT a_f32,
		TFLOAT a_f33,
		TFLOAT a_f34,
		TFLOAT a_f41,
		TFLOAT a_f42,
		TFLOAT a_f43,
		TFLOAT a_f44)
	{
		m_f11 = a_f11;
		m_f12 = a_f12;
		m_f13 = a_f13;
		m_f14 = a_f14;
		m_f21 = a_f21;
		m_f22 = a_f22;
		m_f23 = a_f23;
		m_f24 = a_f24;
		m_f31 = a_f31;
		m_f32 = a_f32;
		m_f33 = a_f33;
		m_f34 = a_f34;
		m_f41 = a_f41;
		m_f42 = a_f42;
		m_f43 = a_f43;
		m_f44 = a_f44;
	}

	void Identity()
	{
		*this = IDENTITY;
	}

private:

	static const TMatrix44 IDENTITY;

	TFLOAT m_f11, m_f12, m_f13, m_f14;
	TFLOAT m_f21, m_f22, m_f23, m_f24;
	TFLOAT m_f31, m_f32, m_f33, m_f34;
	TFLOAT m_f41, m_f42, m_f43, m_f44;
};

TOSHI_NAMESPACE_END
