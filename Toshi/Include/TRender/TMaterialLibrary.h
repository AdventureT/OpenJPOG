#pragma once
#include "Defines.h"
#include "TShader.h"
#include "TKernel/TNodeList.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TMaterialLibrary : public TNodeList<TMaterialLibrary>::TNode
{
	friend class TMaterialLibraryManager;
protected:
	TMaterial* GetMaterial(TPCCHAR a_szMaterial);
private:

};

class TRENDERINTERFACE_EXPORTS TMaterialLibraryManager
{
public:
	// $TRenderInterface: FUNCTION 10011020
	void Create();
	// $TRenderInterface: FUNCTION 100110a0
	void Destroy();
	// $TRenderInterface: FUNCTION 1000b0d0
	TMaterial* GetInvalidMaterial()
	{
		return m_pInvalidMaterial;
	}
	// $TRenderInterface: FUNCTION 10011290
	TMaterial* GetMaterial(TPCCHAR a_szMaterial);

private:
	TNodeList<TMaterialLibrary> m_oLibraries; // 0x0
	TMaterial* m_pInvalidMaterial;            // 0x10
};

TOSHI_NAMESPACE_END