@echo off
setlocal ENABLEDELAYEDEXPANSION
:: ----------------------------------------------------
::  Color definitions (ANSI escape sequences)
:: ----------------------------------------------------
for /F "delims=" %%a in ('echo prompt $E^| cmd') do set ESC=%%a
set COL_RESET=%ESC%[0m
set COL_RED=%ESC%[31m
set COL_GREEN=%ESC%[32m
set COL_YELLOW=%ESC%[33m
set COL_BLUE=%ESC%[34m
set COL_MAGENTA=%ESC%[35m
set COL_CYAN=%ESC%[36m

echo %COL_GREEN%=== Polygon_type_traits : CMake Build Script ===%COL_RESET%

:: ----------------------------------------------------
:: 1. Select configuration (default = Release)
echo %COL_CYAN%== 1. Select configuration (default = Release)...%COL_RESET%
:: ----------------------------------------------------

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Release

echo %COL_YELLOW%=== Build type: %CONFIG%%COL_RESET%

:: ----------------------------------------------------
:: 2. Tools auto-detection
echo %COL_CYAN%=== 2. Tools auto-detection...%COL_RESET%
:: ----------------------------------------------------
::set CMAKE_EXE=C:\msys64\mingw64\bin\cmake.exe
set CMAKE_EXE=C:\msys64\clang64\bin\cmake.exe
set NINJA_EXE=ninja

if not exist "%CMAKE_EXE%" (
    echo %COL_RED%ERROR: CMake not found at %CMAKE_EXE%%COL_RESET%
    pause
    exit /b 1
)

where %NINJA_EXE% >nul 2>&1
if errorlevel 1 (
    echo %COL_RED%ERROR: Ninja is required but not found in PATH.%COL_RESET%
    pause
    exit /b 1
)

echo %COL_GREEN%=== Tools detected successfully%COL_RESET%

:: ----------------------------------------------------
:: 3. Build directory
echo %COL_CYAN%=== 3. Build directory...%COL_RESET%
:: ----------------------------------------------------
set BUILD_DIR=build_%CONFIG%

if not exist "%BUILD_DIR%" (
    echo %COL_BLUE%=== Creating build directory %BUILD_DIR%%COL_RESET%
    mkdir "%BUILD_DIR%"
)

:: ----------------------------------------------------
:: 4. Configure CMake
echo %COL_CYAN%=== 4. Configure CMake...%COL_RESET%
:: ----------------------------------------------------
echo %COL_MAGENTA%=== Configuring CMake...%COL_RESET%

"%CMAKE_EXE%" ^
    -G Ninja ^
    -S . ^
    -B "%BUILD_DIR%" ^
    -D CMAKE_BUILD_TYPE=%CONFIG%

if errorlevel 1 (
    echo %COL_RED%Configuration FAILED.%COL_RESET%
    pause
    exit /b 1
)

echo %COL_GREEN%=== Configuration OK%COL_RESET%

:: ----------------------------------------------------
:: 5. Build
echo %COL_CYAN%=== 5. Build...%COL_RESET%
:: ----------------------------------------------------
echo %COL_MAGENTA%=== Building...%COL_RESET%

"%CMAKE_EXE%" --build "%BUILD_DIR%"

if errorlevel 1 (
    echo %COL_RED%Build FAILED.%COL_RESET%
    pause
    exit /b 1
)

echo %COL_GREEN%=== Build SUCCESS... %COL_RESET%
echo.
pause
exit /b 0