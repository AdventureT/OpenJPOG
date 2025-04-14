project ("TKernelInterface")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"winmm.lib"
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"%{IncludeDir.fmod}"
	}

	defines
	{
		"TKERNELINTERFACE"
	}
	
	libdirs
	{
		"%{LibDir.fmod}"
	}

	filter "system:windows"
		files
		{
			"Include/*.h",
			"resource.h",
			"Icons/Toshi.ico",
			"TKernelInterface.rc",
			"TKernelInterface.aps",
			"Include/TKernel/**.h",
			"Source/TKernel/**.cpp"
		}
		
project ("TApplication")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"winmm.lib",
		"TKernelInterface"
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"Include/TApplication"
	}
	
	files
	{
		"Include/*.h",
		"Include/TApplication/**.h",
		"Source/TApplication/**.cpp"
	}
	
	defines
	{
		"TAPPLICATION"
	}
		
project ("TTerrainInterface")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"winmm.lib",
		"TKernelInterface"
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"Include/TTerrain"
	}
	
	files
	{
		"Include/*.h",
		"Include/TTerrain/**.h",
		"Source/TTerrain/**.cpp"
	}
	
	defines
	{
		"TTERRAININTERFACE"
	}
		
project ("TRenderInterface")
	kind "SharedLib"
	language "C++"
	
	links
	{
		"winmm.lib",
		"TKernelInterface",
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"Include/TRender"
	}

	defines
	{
		"TRENDERINTERFACE"
	}

	filter "system:windows"
		files
		{
			"Include/*.h",
			"Include/TRender/**.h",
			"Source/TRender/**.cpp"
		}

project ("TRenderD3DInterface")
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
		"Include"
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
		"TRENDERINTERFACED3D",
		"SAFESEH=0"
	}
	
	linkoptions "/SAFESEH:NO"

	filter "system:windows"
		files
		{
			"Include/*.h",
			"Include/TRenderD3D/**.h",
			"Source/TRenderD3D/**.cpp"
		}

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
		"Include"
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
			"Include/*.h",
			"Shaders/TSysShader/Include/**.h",
			"Shaders/TSysShader/Source/**.cpp"
		}

project ("TGuiInterface")
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	
	links
	{
		"winmm.lib",
		"TKernelInterface"
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"Include/TGui"
	}
	
	files
	{
		"Include/*.h",
		"Include/TGui/**.h",
		"Source/TGui/**.cpp"
	}
	
	defines
	{
		"TGUIINTERFACE"
	}
