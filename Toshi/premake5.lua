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