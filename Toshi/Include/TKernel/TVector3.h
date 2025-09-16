#pragma once

#include "TDebug.h"
#include "TMath.h"

TOSHI_NAMESPACE_BEGIN

class TKERNELINTERFACE_EXPORTS TVector3
{
public:
	TVector3() = default;
	TVector3(TFLOAT a_fX, TFLOAT a_fY, TFLOAT a_fZ) { Set(a_fX, a_fY, a_fZ); }
	TVector3(TFLOAT floats[3]) { Set(floats); }
	TVector3(const TVector3 &other) { Set(other.m_fX, other.m_fY, other.m_fZ); }

	void Clip(TFLOAT fVal, TFLOAT fVal2);
	void CrossProduct(const TVector3 &, const TVector3 &);

	void RotateX(TFLOAT a_fRotation);
	void RotateY(TFLOAT a_fRotation);
	void RotateZ(TFLOAT a_fRotation);

	void Normalize();

	void Set(const TVector3 &vec)
	{
		TVector3::m_fX = vec.m_fX;
		TVector3::m_fY = vec.m_fY;
		TVector3::m_fZ = vec.m_fZ;
	}

	void Set(TFLOAT floats[3])
	{
		TVector3::m_fX = floats[0];
		TVector3::m_fY = floats[1];
		TVector3::m_fZ = floats[2];
	}

	void Set(TFLOAT m_fX, TFLOAT m_fY, TFLOAT m_fZ)
	{
		TVector3::m_fX = m_fX;
		TVector3::m_fY = m_fY;
		TVector3::m_fZ = m_fZ;
	}

	void Lerp(const TVector3 &finish, float t) { Lerp(*this, finish, t); }

	void Lerp(const TVector3 &start, const TVector3 &finish, float t)
	{
		TVector3 progress = finish - start;
		progress.Multiply(t);

		Set(start + progress);
	}

	void Add(const TVector3 &vec)
	{
		m_fX += vec.m_fX;
		m_fY += vec.m_fY;
		m_fZ += vec.m_fZ;
	}

	void Add(const TVector3 &a, const TVector3 &b)
	{
		Set(a + b);
	}

	void Divide(const TVector3 &vec)
	{
		m_fX /= vec.m_fX;
		m_fY /= vec.m_fY;
		m_fZ /= vec.m_fZ;
	}

	void Divide(TFLOAT scalar)
	{
		TFLOAT ratio = 1.0f / scalar;
		m_fX *= ratio;
		m_fY *= ratio;
		m_fZ *= ratio;
	}

	void Divide(const TVector3 &vec1, const TVector3 &vec2)
	{
		Set(vec1 / vec2);
	}

	void Divide(const TVector3 &vec, TFLOAT scalar)
	{
		Set(vec);
		Divide(scalar);
	}

	void Multiply(const TVector3 &vec)
	{
		m_fX *= vec.m_fX;
		m_fY *= vec.m_fY;
		m_fZ *= vec.m_fZ;
	}

	void Multiply(TFLOAT scalar)
	{
		m_fX *= scalar;
		m_fY *= scalar;
		m_fZ *= scalar;
	}

	void Multiply(const TVector3 &vec1, const TVector3 &vec2)
	{
		Set(vec1 * vec2);
	}

	void Multiply(const TVector3 &vec, TFLOAT scalar)
	{
		Set(vec);
		Multiply(scalar);
	}

	TBOOL Equals(const TVector3 &vec)
	{
		return vec.m_fX == m_fX && vec.m_fY == m_fY && vec.m_fZ == m_fZ;
	}

	void Abs(const TVector3 &vec3) { Set(TMath::Abs(vec3.m_fX), TMath::Abs(vec3.m_fY), TMath::Abs(vec3.m_fZ)); }
	void Abs() { Set(TMath::Abs(m_fX), TMath::Abs(m_fY), TMath::Abs(m_fZ)); }

	TFLOAT Magnitude() const { return TMath::Sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ); }
	TFLOAT MagnitudeSq() const { return m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ; }

	TVector3 operator+(const TVector3 &other) const { return { m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ }; }
	TVector3 operator-(const TVector3 &other) const { return { m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ }; }
	TVector3 operator*(const TVector3 &other) const { return { m_fX * other.m_fX, m_fY * other.m_fY, m_fZ * other.m_fZ }; }
	TVector3 operator/(const TVector3 &other) const { return { m_fX / other.m_fX, m_fY / other.m_fY, m_fZ / other.m_fZ }; }

	void operator=(const TVector3 &other) { Set(other); }
	void operator+=(const TVector3 &other) { Add(other); }
	void operator/=(const TVector3 &other) { Divide(other); }

	const TFLOAT &operator()(TUINT a_iIndex) const
	{
		return (&m_fX)[a_iIndex];
	}

	TFLOAT &operator()(TUINT a_iIndex)
	{
		return (&m_fX)[a_iIndex];
	}

public:
	static TFLOAT Distance(const TVector3 &vec1, const TVector3 &vec2) { return (vec2 - vec1).Magnitude(); }
	static TFLOAT DistanceSq(const TVector3 &vec1, const TVector3 &vec2) { return (vec2 - vec1).MagnitudeSq(); }
	static TFLOAT DotProduct(const TVector3 &vec1, const TVector3 &vec2) { return vec1.m_fX * vec2.m_fX + vec1.m_fY * vec2.m_fY + vec1.m_fZ * vec2.m_fZ; }

public:
	static const TVector3 VEC_ZERO;
	static const TVector3 VEC_POSX;
	static const TVector3 VEC_POSY;
	static const TVector3 VEC_POSZ;
	static const TVector3 VEC_NEGX;
	static const TVector3 VEC_NEGY;
	static const TVector3 VEC_NEGZ;
	static const TVector3 VEC_NEGXPOSZ;
	static const TVector3 VEC_NEGXNEGZ;
	static const TVector3 VEC_POSXPOSZ;
	static const TVector3 VEC_POSXNEGZ;

private:
	TFLOAT m_fX; // 0x0
	TFLOAT m_fY; // 0x4
	TFLOAT m_fZ; // 0x8
};

TOSHI_NAMESPACE_END
