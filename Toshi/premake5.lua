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
		"TOSHI_USER_ENGINE",
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
		"TOSHI_USER_ENGINE",
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
		"TKernelInterface"
	}

	includedirs
	{
		"Include",
		"Include/TKernel",
		"Include/TRender"
	}

	defines
	{
		"TOSHI_USER_ENGINE",
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
		"TKernelInterface",
		"TRenderInterface"
	}

	includedirs
	{
		"Include",
		"%{IncludeDir.dx8}"
	}

	
	libdirs
	{
		"%{LibDir.dx8}"
	}

	defines
	{
		"TOSHI_USER_ENGINE",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
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