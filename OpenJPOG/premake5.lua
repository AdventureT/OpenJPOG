project ("OpenJPOG")
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"

	links
	{
		"TKernelInterface",
		"TApplication",
		"libtheora",
		"theoraplay"
	}

	files
	{
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include",
	}
	
	defines
	{
		"TOSHI_USER_CLIENT"
	}
	
	postbuildcommands
	{
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TKernelInterface/TKernelInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TApplication/TApplication.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		kind "ConsoleApp"
		runtime "Debug"
		defines "TOSHI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		kind "ConsoleApp"
		runtime "Release"
		defines "TOSHI_RELEASE"
		optimize "On"

	filter "configurations:Final"
		kind "ConsoleApp"
		runtime "Release"
		defines "TOSHI_FINAL"
		optimize "On"
