include "Settings.lua"
include "Dependencies.lua"

workspace ("OpenJPOG")
	cppdialect "C++20"
	characterset "ASCII"
	
	platforms "Windows"
	configurations { "Debug", "Release", "Final" }
	
	disablewarnings { "4996", "4251", "4275" }
	
	debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- Disable precompiled headers for C files
	filter "files:**.c"
		flags { "NoPCH" }

	-- Global defines
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"NOMINMAX"
	}

	-- Windows defines
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOSHI_SKU_WINDOWS"
		}
	
	-- Architectures
	filter "options:arch=x86"
		architecture "x86"
		
	filter "options:arch=x64"
		architecture "x64"

	-- Building modes
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

group "00-Game"
	include "OpenJPOG"

group "10-Engine"
	include "Toshi"

group "10-Engine/11-Shader"
	include "Toshi/Shaders/TSysShader"
	include "Toshi/Shaders/TSpriteShader"

group "20-Plugin"
	include "Toshi/Plugins"
	
--group "Third-Party"
--	include "Toshi/Vendor/libogg"
--	include "Toshi/Vendor/libvorbis"
--	include "Toshi/Vendor/libtheora"
--	include "Toshi/Vendor/theoraplay"

group "30-Tools"
	include "Tools/UnitTests"