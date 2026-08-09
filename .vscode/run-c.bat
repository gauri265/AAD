@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x64 >nul
cd /d "%~dp1"

cl "%~nx1" /Fe:"%~dpn1.exe"

if errorlevel 1 exit /b %errorlevel%

"%~dpn1.exe"

del "%~dpn1.exe" >nul 2>&1
del "%~dpn1.obj" >nul 2>&1