IncludeDir = {}
IncludeDir.fmod = "%{wks.location}/Toshi/vendor/fmod/include"
IncludeDir.bink = "%{wks.location}/Toshi/vendor/bink/include"
IncludeDir.libogg = "%{wks.location}/Toshi/Vendor/libogg/include"
IncludeDir.libvorbis = "%{wks.location}/Toshi/Vendor/libvorbis/include"
IncludeDir.libtheora = "%{wks.location}/Toshi/Vendor/libtheora/include"
IncludeDir.theoraplay = "%{wks.location}/Toshi/Vendor/theoraplay/include"
IncludeDir.stb = "%{wks.location}/Toshi/Vendor/stb"
IncludeDir.catch2 = "%{wks.location}/Tools/Vendor/Catch2/include"

LibDir = {}
LibDir.fmod = "%{wks.location}/Toshi/vendor/fmod/lib"
LibDir.bink = "%{wks.location}/Toshi/vendor/bink/lib"
LibDir.catch2 = "%{wks.location}/Tools/Vendor/Catch2/lib"

-- content of these folders should be copied to any client application
ClientContentCommon = "%{wks.location}Content/Common/"
ClientContentArch   = "%{wks.location}Content"

-- modify paths based on architecture
--LibDir.fmod = LibDir.fmod .. "/" .. _OPTIONS["arch"] .. "/"
LibDir.catch2 = LibDir.catch2 .. "/" .. _OPTIONS["arch"] .. "/"
ClientContentArch = ClientContentArch .. "/" .. _OPTIONS["arch"] .. "/"