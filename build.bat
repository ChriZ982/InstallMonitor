@echo off
if defined TRAVIS_TAG ( set "version=%TRAVIS_TAG%" ) else ( set "version=local" )
set build_tools="C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"

set out_dir=build\debug
set compilerflags=/GL /Gy /Zi /Gm- /sdl /Fd"%out_dir%\vc141.pdb" /Zc:inline /MD /EHsc /nologo /Fo"%out_dir%/"
set linkerflags=/PDB:"%out_dir%/InstallMonitor.pdb" /DEBUG /OPT:REF /OPT:ICF
md %out_dir%

call %build_tools% x64
cl.exe %compilerflags% src\*.cpp /link %linkerflags% /OUT:"%out_dir%\InstallMonitor-%version%-win32-%VSCMD_ARG_TGT_ARCH%.exe"

call %build_tools% x86
cl.exe %compilerflags% src\*.cpp /link %linkerflags% /OUT:"%out_dir%\InstallMonitor-%version%-win32-%VSCMD_ARG_TGT_ARCH%.exe"

set out_dir=build\release
set compilerflags=/GL /Gy /Gm- /Ox /sdl /Zc:inline /Oi /MD /EHsc /nologo /Fo"%out_dir%/"
set linkerflags=/OPT:REF /OPT:ICF
md %out_dir%

call %build_tools% x64
cl.exe %compilerflags% src\*.cpp /link %linkerflags% /OUT:"%out_dir%\InstallMonitor-%version%-win32-%VSCMD_ARG_TGT_ARCH%.exe"

call %build_tools% x86
cl.exe %compilerflags% src\*.cpp /link %linkerflags% /OUT:"%out_dir%\InstallMonitor-%version%-win32-%VSCMD_ARG_TGT_ARCH%.exe"