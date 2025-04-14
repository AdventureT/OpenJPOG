#include "TMaterialLibrary.h"
#include "TRender/TRenderInterface.h"

TOSHI_NAMESPACE_BEGIN

TMaterial *TMaterialLibrary::GetMaterial(TPCCHAR a_szMaterial)
{
	return TNULL;
}

void TMaterialLibraryManager::Create()
{
	TMaterial *pSkin = reinterpret_cast<TMaterial *>(TRenderInterface::GetRenderer()->GetSystemResource(TRenderInterface::SYSRESOURCE_SHSKIN));
}

void TMaterialLibraryManager::Destroy()
{
	TASSERT(m_oLibraries.IsEmpty());
	if (m_pInvalidMaterial) {
		m_pInvalidMaterial->PostRender();
		m_pInvalidMaterial = TNULL;
	}
}

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
