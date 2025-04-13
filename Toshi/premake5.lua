project ("TKernelInterface")
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	
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
		"TKERNELINTERFACE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	libdirs
	{
		"%{LibDir.fmod}"
	}
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
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

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"
		
project ("TApplication")
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
		"TAPPLICATION",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"
		
project ("TTerrainInterface")
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
		"TTERRAININTERFACE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"
		
project ("TRenderInterface")
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	
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
		"TRENDERINTERFACE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
		files
		{
			"Include/*.h",
			"Include/TRender/**.h",
			"Source/TRender/**.cpp"
		}

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"

project ("TRenderD3DInterface")
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	
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
		"SAFESEH=0",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	linkoptions "/SAFESEH:NO"
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
		files
		{
			"Include/*.h",
			"Include/TRenderD3D/**.h",
			"Source/TRenderD3D/**.cpp"
		}

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"

project ("TSysShaderD3D")
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	
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
		"SAFESEH=0",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	linkoptions "/SAFESEH:NO"
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
		files
		{
			"Include/*.h",
			"Shaders/TSysShader/Include/**.h",
			"Shaders/TSysShader/Source/**.cpp"
		}

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"

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
		"TGUIINTERFACE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TOSHI_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TOSHI_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Final"
		defines "TOSHI_FINAL"
		runtime "Release"
		optimize "On"