#include "TSpriteShader.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

IMPLEMENT_DYNAMIC(TSpriteMaterial, TMaterial)

IMPLEMENT_DYNAMIC(TSpriteShader, TShader)

void TSpriteShader::SetMaterial(TSpriteMaterial *a_pMaterial)
{
	TIMPLEMENT()
}

void TSpriteShader::SetColour(const TGUIColour &a_rColour)
{
	TIMPLEMENT()
}

void TSpriteShader::BeginMeshGeneration()
{
	TIMPLEMENT()
}

void TSpriteShader::EndMeshGeneration()
{
	TIMPLEMENT()
}

TOSHI_NAMESPACE_END