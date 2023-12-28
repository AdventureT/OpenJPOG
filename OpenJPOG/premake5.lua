project ("OpenJPOG")
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"
	staticruntime "on"

	links
	{
		"TKernelInterface",
		"TApplication",
		"TRenderInterface",
		"fmodvc.lib",
		"binkw32.lib"
	}

	files
	{
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include",
		"%{IncludeDir.fmod}",
		"%{IncludeDir.bink}"
	}
	
	defines
	{
		"TOSHI_USER_CLIENT"
	}
	
	libdirs
	{
		"%{LibDir.fmod}",
		"%{LibDir.bink}"
	}
	
	postbuildcommands
	{
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TKernelInterface/TKernelInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TApplication/TApplication.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}Toshi/vendor/fmod/lib/fmod.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}Toshi/vendor/bink/lib/binkw32.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
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
