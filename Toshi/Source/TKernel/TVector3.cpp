#include "TVector3.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

const TVector3 TVector3::VEC_ZERO     = TVector3(0, 0, 0);
const TVector3 TVector3::VEC_POSX     = TVector3(1, 0, 0);
const TVector3 TVector3::VEC_POSY     = TVector3(0, 1, 0);
const TVector3 TVector3::VEC_POSZ     = TVector3(0, 0, 1);
const TVector3 TVector3::VEC_NEGX     = TVector3(-1, 0, 0);
const TVector3 TVector3::VEC_NEGY     = TVector3(0, -1, 0);
const TVector3 TVector3::VEC_NEGZ     = TVector3(0, 0, -1);
const TVector3 TVector3::VEC_POSXPOSZ = TVector3(TMath::ONEOVER_SQRT_TWO, 0, TMath::ONEOVER_SQRT_TWO);
const TVector3 TVector3::VEC_POSXNEGZ = TVector3(TMath::ONEOVER_SQRT_TWO, 0, -TMath::ONEOVER_SQRT_TWO);
const TVector3 TVector3::VEC_NEGXPOSZ = TVector3(-TMath::ONEOVER_SQRT_TWO, 0, TMath::ONEOVER_SQRT_TWO);
const TVector3 TVector3::VEC_NEGXNEGZ = TVector3(-TMath::ONEOVER_SQRT_TWO, 0, -TMath::ONEOVER_SQRT_TWO);

void TVector3::Clip(TFLOAT fVal, TFLOAT fVal2)
{
	TMath::Clip(m_fX, fVal, fVal2);
	TMath::Clip(m_fY, fVal, fVal2);
	TMath::Clip(m_fZ, fVal, fVal2);
}

void TVector3::CrossProduct(const TVector3 &vec1, const TVector3 &vec2)
{
	TFLOAT fX = vec2.m_fZ * vec1.m_fY - vec2.m_fY * vec1.m_fZ;
	TFLOAT fY = vec1.m_fZ * vec2.m_fX - vec2.m_fZ * vec1.m_fX;
	TFLOAT fZ = vec1.m_fX * vec2.m_fY - vec1.m_fY * vec2.m_fX;
	Set(fX, fY, fZ);
}

void TVector3::RotateX(TFLOAT a_fRotation)
{
	TFLOAT f1;
	TFLOAT f2;
	TFLOAT oldY = m_fY;

	TMath::SinCos(a_fRotation, f1, f2);

	m_fY = -f1 * m_fZ + f2 * oldY;
	m_fZ = oldY * f1 + m_fZ * f2;
}

void TVector3::RotateY(TFLOAT a_fRotation)
{
	TFLOAT f1;
	TFLOAT f2;
	TFLOAT oldX = m_fX;

	TMath::SinCos(a_fRotation, f1, f2);

	m_fX = f1 * m_fZ + f2 * oldX;
	m_fZ = m_fZ * f2 + -f1 * oldX;
}

void TVector3::RotateZ(TFLOAT a_fRotation)
{
	TFLOAT f1;
	TFLOAT f2;
	TFLOAT oldX = m_fX;

	TMath::SinCos(a_fRotation, f1, f2);

	m_fX = -f1 * m_fY + f2 * oldX;
	m_fY = f1 * oldX + m_fY * f2;
}

void TVector3::Normalize()
{
	if (MagnitudeSq() != 0.0f) {
		TFLOAT magnitude = 1.0f / Magnitude();
		Set(m_fX * magnitude, m_fY * magnitude, m_fZ * magnitude);
		return;
	}
	Set(0.0f, 0.0f, 1.0f);
}

TOSHI_NAMESPACE_END
