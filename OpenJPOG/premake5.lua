project ("OpenJPOG")
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"

	links
	{
		"TKernelInterface",
		"TApplication",
		"TRenderInterface",
		"TRenderD3DInterface",
		"TGuiInterface",
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
		"Source",
		"%{wks.location}/Toshi/Include",
		"%{wks.location}/Toshi/Plugins/Include",
		"%{IncludeDir.fmod}",
		"%{IncludeDir.bink}"
	}
	
	externalincludedirs
	{
		"%{IncludeDir.dx8}"
	}
	
	defines
	{
		"TOSHI_USER_CLIENT"
	}
	
	libdirs
	{
		"%{LibDir.fmod}",
		"%{LibDir.bink}",
		"%{LibDir.dx8}"
	}
	
	postbuildcommands
	{
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TKernelInterface/TKernelInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TApplication/TApplication.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TRenderInterface/TRenderInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TRenderD3DInterface/TRenderD3DInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TGuiInterface/TGuiInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/PPropertyParser/PPropertyParser.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}Toshi/vendor/fmod/lib/fmod.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}Toshi/vendor/bink/lib/binkw32.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
	}
