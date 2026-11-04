@echo off
setlocal
pushd "%~dp0"

if not defined CC set CC=cl

set OUT=bin\example.exe

if not exist bin mkdir bin

%CC% /nologo /std:c11 /W4 /Zi /Od "examples\example.c" /Fe:"%OUT%" /Fo:"bin\\" 
if errorlevel 1 (
    echo Build failed.
    popd
    exit /b 1
)

copy /Y "%SDL_DIR%\bin\SDL3.dll" "bin\" >nul
copy /Y "%SDL_DIR%\bin\SDL3_ttf.dll" "bin\" >nul

echo Built %OUT%
popd
endlocal
