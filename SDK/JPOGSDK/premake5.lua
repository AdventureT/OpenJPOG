project "JPOGSDK"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	libdirs
	{
		"%{LibDir.detours}",
	}

	files
	{
		"Include/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"Include",
		"Source",
		"%{wks.location}/Toshi/Include",
		"%{wks.location}/Toshi/Shaders",
		"%{wks.location}/Toshi/Plugins/Include",
	}
	
	externalincludedirs
	{
		"%{IncludeDir.dx8}"
	}
	
	filter "system:windows"
		defines { "TOSHI_SDK" }
