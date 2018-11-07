@echo off
call "C:/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/VC/Auxiliary/Build/vcvarsall.bat" x64

set out_dir=build
set compilerflags=/GL /Gy /Zi /Gm- /Ox /sdl /Fd"%out_dir%/vc141.pdb" /Zc:inline /Oi /MD /EHsc /nologo /Fo"%out_dir%/"
set linkerflags=/OUT:"%out_dir%/InstallMonitor-%TRAVIS_TAG%-win32-x64.exe" /PDB:"%out_dir%/InstallMonitor.pdb" /DEBUG /OPT:REF /OPT:ICF 

mkdir %out_dir%
cl.exe %compilerflags% InstallMonitor.cpp /link %linkerflags%

dir