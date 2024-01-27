project ("PPropertyParser")
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
		"%{wks.location}/Toshi/Include",
		"%{wks.location}/Toshi/Include/TKernel"
	}

	defines
	{
		"PPROPERTYPARSER",
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	
	filter "files:**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
		files
		{
			"Include/*.h",
			"Include/PPropertyParser/**.h",
			"Source/PPropertyParser/**.cpp"
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