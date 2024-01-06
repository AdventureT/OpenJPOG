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
	m_pCurrentRenderContext = TNULL;
	m_pKernel = TNULL;
	m_iResourceCount = 1;
	TCString("Creating TRenderInterface\n").Print();
	TASSERT(s_Interface == TNULL);
	s_Interface = this;
	TSystem::MemSet(m_aSysResources, 0, sizeof(m_aSysResources));
	TCString("Created TRenderInterface\n").Print();
}

TBOOL TRenderInterface::CreateDisplay(const DisplayParams& a_rParams)
{
	return TBOOL();
}

TBOOL TRenderInterface::DestroyDisplay()
{
	return TBOOL();
}

TBOOL TRenderInterface::Update(float a_fDeltaTime)
{
	return TBOOL();
}

TBOOL TRenderInterface::BeginScene()
{
	return TBOOL();
}

TBOOL TRenderInterface::EndScene()
{
	return TBOOL();
}

TRenderAdapter::Mode::Device* TRenderInterface::GetCurrentDevice()
{
	return TNULL;
}

TRenderInterface::DisplayParams* TRenderInterface::GetCurrentDisplayParams()
{
	return nullptr;
}


TBOOL TRenderInterface::Create(TKernelInterface* pKernelInterface)
{
	TASSERT(TFALSE == IsCreated());
	TVALIDADDRESS(pKernelInterface);

	m_pKernel = pKernelInterface;
	return TTRUE;
}

TBOOL TRenderInterface::CreateSystemResources()
{
	{
		TCString("  Adding base resources\n").Print();
	}

	TBOOL bRes = TFALSE;
	TVertexFactoryFormat vertexFormat;

	m_aSysResources[SYSRESOURCE_VFACTORIES] = CreateResource(&TGetClass(TNullResource), "VFactories", TNULL);

	m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1] = CreateResource(TFindClass(TVertexFactoryResource, TNULL), "VFSYSSVNDUV1", GetSystemResource(SYSRESOURCE_VFACTORIES));
	TVALIDADDRESS(m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1]);
	vertexFormat.m_uiNumStreams = 1;
	vertexFormat.m_aStreamFormats[0].m_uiVertexSize = 24;
	vertexFormat.m_aStreamFormats[0].m_uiUnk = 0;
	bRes = static_cast<TVertexFactoryResourceInterface*>(GetSystemResource(SYSRESOURCE_VFSYSSVNDUV1))->Create(&vertexFormat, 11000, 0);
	TASSERT(TTRUE == bRes);

	m_aSysResources[SYSRESOURCE_VFSKIN] = CreateResource(TFindClass(TVertexFactoryResource, TNULL), "VFSKIN", GetSystemResource(SYSRESOURCE_VFACTORIES));
	TVALIDADDRESS(m_aSysResources[SYSRESOURCE_VFSKIN]);
	vertexFormat.m_uiNumStreams = 1;
	vertexFormat.m_aStreamFormats[0].m_uiVertexSize = 40;
	vertexFormat.m_aStreamFormats[0].m_uiUnk = 0;
	bRes = static_cast<TVertexFactoryResourceInterface*>(GetSystemResource(SYSRESOURCE_VFSKIN))->Create(&vertexFormat, 11000, 0);
	TASSERT(TTRUE == bRes);

	m_aSysResources[SYSRESOURCE_TEXTUREFACTORY] = CreateResource(TFindClass(TTextureFactoryHAL, TNULL), "TextureFactory", TNULL);
	bRes = m_aSysResources[SYSRESOURCE_TEXTUREFACTORY]->Create();
	TASSERT(TTRUE==bRes);

	return TTRUE;
}

void TRenderInterface::DestroySystemResources()
{
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

TBOOL TRenderInterface::Destroy()
{
	return TBOOL();
}

void TRenderInterface::RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
}

void TRenderInterface::DumpStats()
{
}

void TRenderInterface::GetScreenOffset(TVector2& a_rVec)
{
}

void TRenderInterface::SetScreenOffset(const TVector2& a_rVec)
{
}

float TRenderInterface::GetScreenAspectRatio()
{
	return 0.0f;
}

float TRenderInterface::GetPixelAspectRatio()
{
	return 0.0f;
}

TBOOL TRenderInterface::SetPixelAspectRatio(float a_fPixelAspectRatio)
{
	return TBOOL();
}

TRenderContext* TRenderInterface::CreateRenderContext()
{
	return nullptr;
}

TRenderCapture* TRenderInterface::CreateCapture()
{
	return nullptr;
}

void TRenderInterface::DestroyCapture(TRenderCapture* a_pRenderCapture)
{
}

void TRenderInterface::SetLightDirectionMatrix(const TMatrix44& a_rMatrix)
{
}

void TRenderInterface::SetLightColourMatrix(const TMatrix44& a_rMatrix)
{
}

void TRenderInterface::ConnectDefaultViewportHandelrs(TViewport& a_pViewport)
{
}

TModel* TRenderInterface::CreateModel(TPCCHAR a_szName, TINT a_iUnk1)
{
	return nullptr;
}
