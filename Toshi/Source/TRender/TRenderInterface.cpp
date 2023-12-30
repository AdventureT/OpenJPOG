#include "TRenderInterface.h"
#include "TSystemTools.h"
#include "TNullResource.h"
#include "TVertexFactoryResourceInterface.h"

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TRenderInterface, TObject)

TRenderInterface* TRenderInterface::s_Interface = TNULL;

TRenderInterface::TRenderInterface()
{
	m_bIsCreated = TFALSE;
	m_pDefaultRenderContext = TNULL;
	m_pKernel = TNULL;
	TASSERT(s_Interface == TNULL);
	s_Interface = this;
	TSystem::MemSet(m_aSysResources, 0, sizeof(m_aSysResources));
}


TBOOL TRenderInterface::Create(TKernelInterface* pKernelInterface)
{
	TASSERT(TFALSE == IsCreated());
	TVALIDADDRESS(pKernelInterface);

	m_pKernel = pKernelInterface;
	return TTRUE;
}

class TVertexFactoryResource : public TVertexFactoryFormat, public TResource
{
	DECLARE_DYNAMIC(TVertexFactoryResource)
};

IMPLEMENT_DYNCREATE(TVertexFactoryResource, TResource)

TBOOL TRenderInterface::CreateSystemResources()
{
	{
		TCString("  Adding base resources\n").Print();
	}

	m_aSysResources[SYSRESOURCE_VFACTORIES] = CreateResource(&TGetClass(TNullResource), "VFactories", TNULL);
	m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1] = CreateResource(TFindClass(TVertexFactoryResource, TNULL), "VFSYSSVNDUV1", GetSystemResource(SYSRESOURCE_VFACTORIES));
	TVALIDADDRESS(m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1]);

	return TBOOL();
}

TResource* TRenderInterface::CreateResource(const TClass* a_pClass, TPCCHAR a_szResName, TResource* a_pParent)
{
	TASSERT(TNULL != a_pClass);
	TASSERT(a_pClass->IsA(TGetClass(TResource)));

	TResource* pResource = (TResource*)a_pClass->CreateObject();
	TASSERT(TNULL != pResource);

	if (a_pParent && a_pParent->IsDying()) {
		TASSERT(!"Can't add a resource below a dying resource!")
	}

	m_Resources.Remove(*pResource, TFALSE);

	if (a_pParent == TNULL)
	{
		a_pParent = m_Resources.GetRoot();
	}

	m_Resources.Insert(a_pParent, pResource);
	pResource->m_uiUId = m_iResourceCount++;
	pResource->m_pRenderer = this;
	pResource->SetName(a_szResName);

	return pResource;
}
