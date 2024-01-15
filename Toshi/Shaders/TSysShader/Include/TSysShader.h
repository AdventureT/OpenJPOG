#pragma once

#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class ASysMaterial;
class ASysMesh;

class TSYSSHADERD3D_EXPORTS TSysShader
{
public:
	virtual ASysMaterial* CreateMaterial(const char* a_szName) = 0;
	virtual ASysMesh* CreateMesh(const char* a_szName) = 0;
};

TOSHI_NAMESPACE_END