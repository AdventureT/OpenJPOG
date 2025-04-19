project ("TSysShaderD3D")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"d3d8.lib",
		"d3dx8.lib",
		"dxguid.lib",
		"dxgi.lib",
		"DxErr8.lib",
		"legacy_stdio_definitions.lib",
		"winmm.lib",
		"dinput8.lib",
		"TKernelInterface",
		"TRenderInterface"
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include"
	}
	
	externalincludedirs
	{
		"%{IncludeDir.dx8}"
	}

	libdirs
	{
		"%{LibDir.dx8}"
	}

	defines
	{
		"TSYSSHADERD3D",
		"SAFESEH=0"
	}
	
	linkoptions "/SAFESEH:NO"

	filter "system:windows"
		files
		{
			"TSysShader/Include/**.h",
			"TSysShader/Source/**.cpp"
		}

project ("TSpriteShaderD3D")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"d3d8.lib",
		"d3dx8.lib",
		"dxguid.lib",
		"dxgi.lib",
		"DxErr8.lib",
		"legacy_stdio_definitions.lib",
		"winmm.lib",
		"dinput8.lib",
		"TKernelInterface",
		"TRenderInterface"
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include"
	}
	
	externalincludedirs
	{
		"%{IncludeDir.dx8}"
	}

	libdirs
	{
		"%{LibDir.dx8}"
	}

	defines
	{
		"TSPRITESHADERD3D",
		"SAFESEH=0"
	}
	
	linkoptions "/SAFESEH:NO"

	filter "system:windows"
		files
		{
			"TSpriteShader/Include/**.h",
			"TSpriteShader/Source/**.cpp"
		}
