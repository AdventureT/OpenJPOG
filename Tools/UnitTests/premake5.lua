function ExtractLib(options)
	local catch2Location = "../Vendor/Catch2/lib/" .. _OPTIONS["arch"]
	local zipLocation = catch2Location .. "/Catch2" .. options.dbg .. ".zip"
	local libLocation = catch2Location .. "/Catch2" .. options.dbg .. ".lib"
	
	if not os.isfile(libLocation) then
		zip.extract(zipLocation, catch2Location)
	end
end


project "UnitTests"
	kind "ConsoleApp"
	language "C++"

	links
	{
		"TKernelInterface",
		"TApplication",
		"TRenderInterface"
	}
	
	libdirs
	{
		"%{LibDir.catch2}",
	}
		
	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"%{wks.location}/Toshi/Include/*.h",
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include",
		"%{IncludeDir.catch2}"
	}
	
	defines
	{
		"TOSHI_USER_CLIENT"
	}
	
	postbuildcommands
	{
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TKernelInterface/TKernelInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TApplication/TApplication.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TRenderInterface/TRenderInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\""
	}

	filter "system:windows"
		defines "TOSHI_CONSOLE"

	filter "configurations:Debug"
		ExtractLib { dbg = "d" }
		
		links "Catch2d.lib"

	filter "configurations:Release"
		ExtractLib { dbg = "" }
		
		links "Catch2.lib"

	filter "configurations:Final"
		ExtractLib { dbg = "" }
		
		links "Catch2.lib"
		