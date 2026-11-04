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


echo Built %OUT%
popd
endlocal
