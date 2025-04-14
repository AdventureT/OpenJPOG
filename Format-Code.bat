@echo off
set clang_format=%cd%\vendor\clang-format.exe
set directories=(OpenJPOG\Source, OpenJPOG\Include, Toshi\Source, Toshi\Include, Toshi\Plugins\Source, Toshi\Plugins\Include)

for %%P in %directories% do (for %%G in (.cpp, .hpp, .h) do forfiles /p .\%%P\ /s /m *%%G /c "cmd /c %clang_format% -i @path")