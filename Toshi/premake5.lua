project ("TKernel")
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	characterset "ASCII"
	
	links
	{
		"fmod_vc.lib",
		"fmodstudio_vc.lib",
		"fsbank_vc.lib",
		"d3d11.lib",
		"d3dcompiler.lib",
		"dxguid.lib",
		"dxgi.lib",
		"winmm.lib",
		"dinput8.lib",
		"dbghelp.lib"
	}

	includedirs
	{
		"Source",
		"%{IncludeDir.fmod}",
		"%{IncludeDir.stb}"
	}
	
	libdirs
	{
		"%{LibDir.fmod}"
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
			"Include/TKernel/**.h",
			"Source/TKernel/**.cpp",
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

	filter "configurations:Dist"
		defines "TOSHI_DIST"
		runtime "Release"
		optimize "On"