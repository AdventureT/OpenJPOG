#include "TMaterialLibrary.h"
#include "TRender/TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

// $TRenderInterface: FUNCTION 1000ff40
TMaterial *TMaterialLibrary::GetMaterial(TPCCHAR a_szMaterial)
{
	return TNULL;
}

// $TRenderInterface: FUNCTION 10011020
void TMaterialLibraryManager::Create()
{
	TMaterial *pSkin = reinterpret_cast<TMaterial *>(TRenderInterface::GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSKIN));
}

// $TRenderInterface: FUNCTION 100110a0
void TMaterialLibraryManager::Destroy()
{
	TASSERT(m_oLibraries.IsEmpty());
	if (m_pInvalidMaterial) {
		m_pInvalidMaterial->PostRender();
		m_pInvalidMaterial = TNULL;
	}
}

// $TRenderInterface: FUNCTION 10011290
TMaterial *TMaterialLibraryManager::GetMaterial(TPCCHAR a_szMaterial)
{
	if (m_oLibraries.IsEmpty()) {
		TDPRINTF("******** TMaterialLibraryManager::GetMaterial(%s) FAILED!!!!!!! **********\n", a_szMaterial);
		return m_pInvalidMaterial;
	}
	for (auto it = m_oLibraries.Begin(); it != m_oLibraries.End(); it++) {
		TMaterial *pMat = it->GetMaterial(a_szMaterial);
		if (pMat) {
			return pMat;
		}
	}
	return TNULL;
}

TOSHI_NAMESPACE_END
