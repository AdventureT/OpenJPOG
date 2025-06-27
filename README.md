# OpenJPOG
Decompilation of the Toshi engine 1.0 and Jurassic Park: Operation Genesis (JPOG).

## Status
<img src="https://opentoshi.net/progress/JPOG.svg" width="100%"/>
<img src="https://opentoshi.net/progress/TKernelInterface.svg" width="50%"/><img src="https://opentoshi.net/progress/TRenderInterface.svg" width="50%"/>
<img src="https://opentoshi.net/progress/PPropertyParser.svg" width="50%"/>

At the moment, this is not an accurate representation of the actual progress of the decomp, since many functions have not been marked as done.

> [!IMPORTANT] 
> **SUPPORT THE DEVELOPERS OF THE TOSHI ENGINE**
>
> We do not own the Toshi Engine in any way, shape or form, and this project would not have been possible had they not developed TOSHI in the first place. The Toshi Engine is currently owned by [THQ Nordic](https://www.thqnordic.com); we highly urge you to follow & support their projects if you like this project!

> [!WARNING]
> **DO NOT USE THIS DECOMPILATION PROJECT AS A MEANS TO PIRATE JPOG OR ANY OTHER TOSHI GAMES.**
>
> We do not condone using this project as a means for piracy in any form. This project was made with love and care for the source material and was created for purely educational purposes.

## Building

### Windows

Building on Windows requires

- Visual Studio 2019/2022

Clone the repository with the following commands:

	git clone https://github.com/AdventureT/OpenJPOG.git
	cd OpenJPOG
	git submodule update --init --recursive
	./GenerateProjects-VS2019.bat (if you use Visual Studio 2019)
	./GenerateProjects-VS2022.bat (if you use Visual Studio 2022)

Then compile the generated solution and that's it

## Thirdparty libraries
- [catch2](https://github.com/catchorg/Catch2)
- [fmod](https://fmod.com/)
- [premake](https://github.com/premake/premake-core)
- [spdlog](https://github.com/gabime/spdlog)
- [bink](http://www.radgametools.com/bnkmain.htm)
- Fork of [theoraplay](https://github.com/InfiniteC0re/theoraplay)
