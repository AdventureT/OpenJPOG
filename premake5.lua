include "Settings.lua"
include "Dependencies.lua"

workspace ("OpenJPOG")
	platforms "Windows"
	configurations { "Debug", "Release", "Final" }
	
	disablewarnings { "4996" }
	
	debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	filter "options:arch=x86"
		architecture "x86"
		
	filter "options:arch=x64"
		architecture "x64"

group "Engine"
	include "Toshi"
	include "OpenJPOG"

group "Plugin"
	include "Toshi/Plugins"
	
--group "Third-Party"
--	include "Toshi/Vendor/libogg"
--	include "Toshi/Vendor/libvorbis"
--	include "Toshi/Vendor/libtheora"
--	include "Toshi/Vendor/theoraplay"

group "Tools"
	include "Tools/UnitTests"