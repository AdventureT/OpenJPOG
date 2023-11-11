function ExtractLib(options)
	local catch2Location = "../Vendor/Catch2/lib/" .. _OPTIONS["arch"]
	local zipLocation = catch2Location .. "/Catch2" .. options.dbg .. ".zip"
	local libLocation = catch2Location .. "/Catch2" .. options.dbg .. ".lib"
	
	if not os.isfile(libLocation) then
		zip.extract(zipLocation, catch2Location)
	end
end


project "UnitTests"
	language "C++"
	cppdialect "C++20"
	characterset "ASCII"

	links
	{
		"TKernelInterface"
	}
	
	libdirs
	{
		"%{LibDir.catch2}",
	}
		
	files
	{
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/Toshi/Include",
		"%{IncludeDir.catch2}"
	}
	
	defines
	{
		"TOSHI_USER_CLIENT",
	}
	
	postbuildcommands
	{
		"{COPY} \"%{wks.location}bin/" .. outputdir .. "/TKernelInterface/TKernelInterface.dll\" \"%{wks.location}bin/" .. outputdir .. "/%{prj.name}\"",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_CONSOLE",
			"TOSHI_SKU_WINDOWS"
		}

	filter "configurations:Debug"
		kind "ConsoleApp"
		runtime "Debug"
		defines "TOSHI_DEBUG"
		symbols "On"
		
		ExtractLib { dbg = "d" }
		
		links
		{
			"Catch2d.lib"
		}

	filter "configurations:Release"
		kind "ConsoleApp"
		runtime "Release"
		defines "TOSHI_RELEASE"
		optimize "On"
		
		ExtractLib { dbg = ""}
		
		links
		{
			"Catch2.lib"
		}

	filter "configurations:Dist"
		kind "ConsoleApp"
		runtime "Release"
		defines "TOSHI_DIST"
		optimize "On"
		
		ExtractLib { dbg = "" }
		
		links
		{
			"Catch2.lib"
		}

		