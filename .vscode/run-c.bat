@echo off

set "file=%~1"
set "dir=%~dp1"
set "name=%~n1"

cd /d "%dir%"

"C:\msys64\ucrt64\bin\gcc.exe" "%file%" -o "%name%.exe"

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b
)

echo.
echo Running %name%.exe...
echo.

"%name%.exe"

echo.
echo Program finished.

del /Q "%name%.exe" 2>nul