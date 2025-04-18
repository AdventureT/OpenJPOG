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
		"PPROPERTYPARSER"
	}

	filter "system:windows"
		files
		{
			"Include/*.h",
			"Include/PPropertyParser/**.h",
			"Source/PPropertyParser/**.cpp"
		}

project ("PGui")
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
		"PGUI"
	}

	filter "system:windows"
		files
		{
			"Include/*.h",
			"Include/PGui/**.h",
			"Source/PGui/**.cpp"
		}