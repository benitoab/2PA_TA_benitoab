@ECHO OFF

del *.obj *.pdb *.ilk *.exe
cls
cl /nologo /Zi /EHs /MDd /W4 -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui\ -I ..\deps\imgui_sdl /c ..\deps\imgui\*.cpp
cl /nologo /Zi /EHs /MDd /W4 -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui\ -I ..\deps\imgui_sdl /c ..\deps\imgui_sdl\imgui_sdl.cpp
cl /nologo /Zi /EHs /MDd /W4 -I ..\include -I ..\deps\sdl2\include -I ..\deps\imgui\ -I ..\deps\imgui_sdl /c ..\src\*.cc
cl /nologo /Zi /EHs /MDd /W4 /Fe: ..\bin\main.exe *.obj /link /SUBSYSTEM:CONSOLE ..\deps\sdl2\lib\x86\SDL2.lib ..\deps\sdl2\lib\x86\SDL2main.lib ..\deps\sdl2\lib\x86\SDL2_image.lib ..\deps\sdl2\lib\x86\SDL2_ttf.lib ..\deps\sql\lib\sqlite.lib opengl32.lib shell32.lib user32.lib gdi32.lib