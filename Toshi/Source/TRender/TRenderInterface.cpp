#include "TRenderInterface.h"
#include "TSystemTools.h"
#include "TNullResource.h"
#include "TVertexFactoryResourceInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNAMIC(TRenderInterface, TObject)

TRenderInterface *TRenderInterface::s_Interface = TNULL;

// $TRenderInterface: FUNCTION 1000cd70
TRenderInterface::TRenderInterface()
{
	m_bIsCreated            = TFALSE;
	m_bIsDiplayCreated      = TFALSE;
	m_pDefaultRenderContext = TNULL;
	m_pCurrentRenderContext = TNULL;
	m_pKernel               = TNULL;
	m_iResourceCount        = 1;
	TCString("Creating TRenderInterface\n").Print();
	TASSERT(s_Interface == TNULL);
	s_Interface = this;
	TSystem::MemSet(m_aSysResources, 0, sizeof(m_aSysResources));
	TCString("Created TRenderInterface\n").Print();
}

// $TRenderInterface: FUNCTION 1000d2e0
TBOOL TRenderInterface::CreateDisplay(const DisplayParams &a_rParams)
{
	TASSERT(TTRUE == IsCreated());
	TASSERT(TFALSE == IsDisplayCreated());
	m_bIsDiplayCreated = 1;
	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000d360
TBOOL TRenderInterface::DestroyDisplay()
{
	TASSERT(TTRUE == IsCreated());
	m_bIsDiplayCreated = TFALSE;
	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000f290
TBOOL TRenderInterface::Update(float a_fDeltaTime)
{
	FlushDyingResources();
	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000d3b0
TBOOL TRenderInterface::BeginScene()
{
	TASSERT(TTRUE == IsCreated());
	TASSERT(TTRUE == IsDisplayCreated());
	m_iSceneCount++;
	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000d430
TBOOL TRenderInterface::EndScene()
{
	TASSERT(TTRUE == IsCreated());
	TASSERT(TTRUE == IsDisplayCreated());
	return TTRUE;
}

TRenderAdapter::Mode::Device *TRenderInterface::GetCurrentDevice()
{
	return TNULL;
}

TRenderInterface::DisplayParams *TRenderInterface::GetCurrentDisplayParams()
{
	return nullptr;
}

// $TRenderInterface: FUNCTION 1000d4b0
TBOOL TRenderInterface::Create(TKernelInterface *pKernelInterface)
{
	TASSERT(TFALSE == IsCreated());

	TVALIDADDRESS(pKernelInterface);
	m_pKernel = pKernelInterface;

	m_pDefaultRenderContext = CreateRenderContext();
	TVALIDADDRESS(m_pDefaultRenderContext);

	if (m_pDefaultRenderContext) {
		SetCurrentRenderContext(m_pDefaultRenderContext);
		m_bIsCreated = TTRUE;
		return TTRUE;
	}
	return TFALSE;
}

// $TRenderInterface: FUNCTION 1000e6b0
TBOOL TRenderInterface::CreateSystemResources()
{
	TCString("  Adding base resources\n").Print();

	TBOOL                bRes = TFALSE;
	TVertexFactoryFormat vertexFormat;

	m_aSysResources[SYSRESOURCE_VFACTORIES] = CreateResource(&TGetClass(TNullResource), "VFactories", TNULL);

	m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1] = CreateResource(TFindClass(TVertexFactoryResource, TNULL), "VFSYSSVNDUV1", GetSystemResource(SYSRESOURCE_VFACTORIES));
	TVALIDADDRESS(m_aSysResources[SYSRESOURCE_VFSYSSVNDUV1]);
	vertexFormat.m_uiNumStreams                     = 1;
	vertexFormat.m_aStreamFormats[0].m_uiVertexSize = 24;
	vertexFormat.m_aStreamFormats[0].m_uiUnk        = 0;
	bRes                                            = static_cast<TVertexFactoryResourceInterface *>(GetSystemResource(SYSRESOURCE_VFSYSSVNDUV1))->Create(&vertexFormat, 11000, 0);
	TASSERT(TTRUE == bRes);

	m_aSysResources[SYSRESOURCE_VFSKIN] = CreateResource(TFindClass(TVertexFactoryResource, TNULL), "VFSKIN", GetSystemResource(SYSRESOURCE_VFACTORIES));
	TVALIDADDRESS(m_aSysResources[SYSRESOURCE_VFSKIN]);
	vertexFormat.m_uiNumStreams                     = 1;
	vertexFormat.m_aStreamFormats[0].m_uiVertexSize = 40;
	vertexFormat.m_aStreamFormats[0].m_uiUnk        = 0;
	bRes                                            = static_cast<TVertexFactoryResourceInterface *>(GetSystemResource(SYSRESOURCE_VFSKIN))->Create(&vertexFormat, 11000, 0);
	TASSERT(TTRUE == bRes);

	m_aSysResources[SYSRESOURCE_TEXTUREFACTORY] = CreateResource(TFindClass(TTextureFactoryHAL, TNULL), "TextureFactory", TNULL);
	bRes                                        = m_aSysResources[SYSRESOURCE_TEXTUREFACTORY]->Create();
	TASSERT(TTRUE == bRes);

	return TTRUE;
}

// $TRenderInterface: FUNCTION 1000f100
void TRenderInterface::DestroySystemResources()
{
}

// $TRenderInterface: FUNCTION 1000def0
TResource *TRenderInterface::CreateResource(const TClass *a_pClass, TPCCHAR a_szResName, TResource *a_pParent)
{
	TASSERT(TNULL != a_pClass);
	TASSERT(a_pClass->IsA(TGetClass(TResource)));

	TResource *pResource = (TResource *)a_pClass->CreateObject();
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
	pResource->m_uiUId     = m_iResourceCount++;
	pResource->m_pRenderer = this;
	pResource->SetName(a_szResName);

	return pResource;
}

// $TRenderInterface: FUNCTION 1000da40
const TRenderAdapter::Mode::Device *TRenderInterface::FindDevice(const DisplayParams *a_pDisplayParams)
{
	auto pAdapter = GetAdapterList()->Begin();

	while (TTRUE)
	{
		if (pAdapter == GetAdapterList()->End())
		{
			TCString().Format("Unable to find the passed device!\n");
			return TNULL;
		}

		for (auto pMode = pAdapter->GetModeList()->Begin(); pMode != pAdapter->GetModeList()->End(); pMode++)
		{
			auto uiNumSupportedDevices = pAdapter->GetNumSupportedDevices();

			for (TUINT32 i = 0; i < uiNumSupportedDevices; i++)
			{
				auto pDevice = pMode->GetDevice(i);

				if (pDevice->IsSoftware()) continue;

				TBOOL bPassedColourDepth = TTRUE;

				if (a_pDisplayParams->uiColourDepth == 32)
				{
					if (!pDevice->GetMode()->Is32Bit())
					{
						bPassedColourDepth = TFALSE;
					}
				}
				else if (a_pDisplayParams->uiColourDepth == 16)
				{
					if (!pDevice->GetMode()->Is16Bit())
					{
						bPassedColourDepth = TFALSE;
					}
				}

				TBOOL bPassedWindowed = TTRUE;

				if (a_pDisplayParams->bWindowed && !pDevice->CanRenderWindowed())
				{
					bPassedWindowed = TFALSE;
				}

				auto uiWidth  = pDevice->GetMode()->GetWidth();
				auto uiHeight = pDevice->GetMode()->GetHeight();

				if (uiHeight < uiWidth || !a_pDisplayParams->bWindowed || a_pDisplayParams->uiWidth <= a_pDisplayParams->uiHeight)
				{
					if (uiWidth == a_pDisplayParams->uiWidth && uiHeight == a_pDisplayParams->uiHeight)
					{
						if (pDevice->IsDepthStencilFormatSupported(a_pDisplayParams->eDepthStencilFormat) &&
						    bPassedColourDepth && bPassedWindowed)
						{
							return pDevice;
						}
					}
				}
				else
				{
					if (a_pDisplayParams->uiWidth <= uiWidth)
					{
						if (uiHeight < a_pDisplayParams->uiHeight) continue;

						if (pDevice->IsDepthStencilFormatSupported(a_pDisplayParams->eDepthStencilFormat) &&
						    bPassedColourDepth && bPassedWindowed)
						{
							return pDevice;
						}
					}
				}
			}
		}

		pAdapter++;
	}
}

// $TRenderInterface: FUNCTION 1000e380
void TRenderInterface::FlushDyingResources()
{
	while (m_bHasDyingResources)
	{
		m_bHasDyingResources = TFALSE;
		DestroyDyingResources(m_Resources.ChildOfRoot());
	}
}

// $TRenderInterface: FUNCTION 1000ec90
void TRenderInterface::DestroyDyingResources(TResource *a_pResource)
{
	// TODO: refactor
	TResource *pTVar1;
	TResource *next;
	TResource *pRes1;
	TResource *pRes2;

	pRes1 = a_pResource;
	pRes2 = a_pResource;
	if (a_pResource) {
		do {
			next = pRes2->Next();
			if (next == pRes1) {
				next = (TResource *)0x0;
			}
			if ((pRes2->m_Flags & 4) == 0) {
				pRes2 = pRes2->Child();
				if (pRes2 != (TResource *)0x0) {
					DestroyDyingResources(pRes2);
				}
			}
			else {
				if (pRes2 == pRes1) {
					pRes1       = next;
					a_pResource = next;
				}
				pTVar1 = pRes2->Child();
				while (pTVar1 != (TResource *)0x0) {
					pRes1 = pTVar1->Next();
					if (pRes1 == pTVar1) {
						pRes1 = (TResource *)0x0;
					}
					DeleteResourceAtomic(pTVar1);
					pTVar1 = pRes1;
					pRes1  = a_pResource;
				}
				DeleteResourceAtomic(pRes2);
			}
			pRes2 = next;
		} while (next);
	}
}

// $TRenderInterface: FUNCTION 1000f090
void TRenderInterface::DeleteResource(TResource *a_pResource)
{
	DeleteResourceRecurse(a_pResource->Child());
	DeleteResourceAtomic(a_pResource);
}

// $TRenderInterface: FUNCTION 1000eda0
void TRenderInterface::DeleteResourceRecurse(TResource *a_pResource)
{
	while (a_pResource)
	{
		auto next = a_pResource->Next();
		if (next == a_pResource) next = TNULL;

		DeleteResourceAtomic(a_pResource);
		a_pResource = next;
	}
}

// $TRenderInterface: FUNCTION 1000edf0
void TRenderInterface::DeleteResourceAtomic(TResource *a_pResource)
{
	if (a_pResource) {
		DeleteResourceRecurse(a_pResource->Child());

		TASSERT(TFALSE == a_pResource->IsValid());

		if (a_pResource->IsCreated()) {
			a_pResource->OnDestroy();
		}

		m_Resources.Remove(a_pResource, TFALSE);

		if (a_pResource->m_Flags & 8) {
			a_pResource->~TResource();
		}
		else {
			delete a_pResource;
		}
	}
}

// $TRenderInterface: FUNCTION 1000d590
TBOOL TRenderInterface::Destroy()
{
	return TBOOL();
}

// $TRenderInterface: FUNCTION 10008bf0
void TRenderInterface::RenderIndexPrimitive(int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
}

// $TRenderInterface: FUNCTION 1000d5d0
void TRenderInterface::DumpStats()
{
}

// $TRenderInterface: FUNCTION 1000f260
void TRenderInterface::GetScreenOffset(TVector2 &a_rVec)
{
}

// $TRenderInterface: FUNCTION 1000f240
void TRenderInterface::SetScreenOffset(const TVector2 &a_rVec)
{
}

// $TRenderInterface: FUNCTION 10008be0
float TRenderInterface::GetScreenAspectRatio()
{
	return 0.0f;
}

// $TRenderInterface: FUNCTION 10008bd0
float TRenderInterface::GetPixelAspectRatio()
{
	return 0.0f;
}

// $TRenderInterface: FUNCTION 10008bc0
TBOOL TRenderInterface::SetPixelAspectRatio(float a_fPixelAspectRatio)
{
	return TBOOL();
}

TRenderContext *TRenderInterface::CreateRenderContext()
{
	return TNULL;
}

TRenderCapture *TRenderInterface::CreateCapture()
{
	return TNULL;
}

void TRenderInterface::DestroyCapture(TRenderCapture *a_pRenderCapture)
{
}

// $TRenderInterface: FUNCTION 10008890
void TRenderInterface::SetLightDirectionMatrix(const TMatrix44 &a_rMatrix)
{
}

// $TRenderInterface: FUNCTION 10008740
void TRenderInterface::SetLightColourMatrix(const TMatrix44 &a_rMatrix)
{
}

void TRenderInterface::ConnectDefaultViewportHandelrs(TViewport &a_pViewport)
{
}

TModel *TRenderInterface::CreateModel(TPCCHAR a_szName, TINT a_iUnk1)
{
	return nullptr;
}
