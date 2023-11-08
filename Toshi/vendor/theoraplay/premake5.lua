project "theoraplay"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	links 
	{
		"libogg",
		"libvorbis",
		"libtheora"
	}

	includedirs
	{
		"include",
		"%{IncludeDir.libogg}",
		"%{IncludeDir.libvorbis}",
		"%{IncludeDir.libtheora}"
	}

	files
	{
		"src/*.c",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"