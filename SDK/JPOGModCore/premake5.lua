project "JPOGModCore"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	links
	{
		"JPOGSDK",
		"TKernelInterface",
		"TApplication",
		"TRenderInterface",
		"TRenderD3DInterface",
		"TGuiInterface",
		"PGUIRenderer",
		"PPropertyParser",
		"d3d8.lib",
		"d3dx8.lib",
		"dxguid.lib",
		"dxgi.lib",
		"DxErr8.lib",
		"dsound.lib",
		"legacy_stdio_definitions.lib",
		"winmm.lib",
		"dinput8.lib",
		"detours.lib",
	}
	
	libdirs
	{
		"%{LibDir.dx8}",
		"%{LibDir.detours}",
	}

	files
	{
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"Source",
		"Include",
		"%{wks.location}/Toshi/Include",
		"%{wks.location}/Toshi/Shaders",
		"%{wks.location}/Toshi/Plugins/Include",
		"%{wks.location}/SDK/JPOGSDK/Include",
		"%{IncludeDir.fmod}",
		"%{IncludeDir.bink}",
		"%{IncludeDir.detours}",
	}
	
	externalincludedirs
	{
		"%{IncludeDir.dx8}"
	}
	
	-- Modloader specific
	debugdir ("%{wks.location}/../Game")
	debugcommand ("%{wks.location}/../Game/JPMod.exe")
	
	postbuildcommands
	{
		"{COPYDIR} \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}/\" %{wks.location}../Game/",
	}

	filter "system:windows"
		defines
		{
			"TOSHI_MODLOADER",
			"TOSHI_SDK"
		}
