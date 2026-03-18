@echo off
setlocal ENABLEDELAYEDEXPANSION

:: 1. Изоляция окружения
set "MSYS_PATH=C:\msys64\mingw64\bin"
set "CMAKE_PATH=C:\Program Files\CMake\bin"
:: set "OPENCV_BIN=D:\LIBRES\OpenCV\bin"
:: set "PATH=%MSYS_PATH%;%CMAKE_PATH%;%OPENCV_BIN%;%SystemRoot%\system32;%SystemRoot%"
set "PATH=%MSYS_PATH%;%CMAKE_PATH%;%SystemRoot%\system32;%SystemRoot%"

echo ===== [DIAGNOSTIC] Checking for zombie processes...
:: Принудительно завершаем старые процессы, которые могут блокировать файлы
taskkill /F /IM Polygon_type_traits.exe /T >nul 2>&1
taskkill /F /IM ninja.exe /T >nul 2>&1

set "BUILD_DIR=build_Release"

echo ===== [1/4] Preparing Build Directory...
if exist "%BUILD_DIR%" rd /s /q "%BUILD_DIR%"
mkdir "%BUILD_DIR%"

echo ===== [2/4] Configuring CMake...
:: Используем call, чтобы скрипт не закрылся при ошибке приложения
call "%MSYS_PATH%\cmake.exe" ^
    -G Ninja ^
    -S . ^
    -B "%BUILD_DIR%" ^
    -D CMAKE_BUILD_TYPE=Release ^
    -D CMAKE_C_COMPILER="%MSYS_PATH%\gcc.exe" ^
    -D CMAKE_CXX_COMPILER="%MSYS_PATH%\g++.exe" ^
    -D CMAKE_MAKE_PROGRAM="%MSYS_PATH%\ninja.exe"

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] CMake configuration failed with code %ERRORLEVEL%
    pause
    exit /b %ERRORLEVEL%
)

echo ===== [3/4] Building Project...
:: Самый опасный момент, где у вас падает скрипт
call "%MSYS_PATH%\cmake.exe" --build "%BUILD_DIR%"

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Build execution failed with code %ERRORLEVEL%
    pause
    exit /b %ERRORLEVEL%
)

echo ===== [4/4] Deploying DLLs...
:: Копируем только в корень папки build_Release, где обычно лежит exe
:: xcopy /y /d "%OPENCV_BIN%\*.dll" "%BUILD_DIR%\"

echo.
echo ===== [5/5] Testing Execution =====

:: Ищем файл рекурсивно внутри папки сборки
set "EXE_PATH="
for /r "%BUILD_DIR%" %%f in (Polygon_type_traits.exe) do (
    if exist "%%f" set "EXE_PATH=%%f"
)

if defined EXE_PATH (
    echo Found: %EXE_PATH%
    :: Переходим в папку, где лежит EXE (чтобы он видел DLL рядом)
    for %%i in ("%EXE_PATH%") do cd /d "%%~dpi"
    
    :: Запускаем
    Polygon_type_traits.exe
) else (
    echo %COL_RED%[ERROR] Polygon_type_traits.exe not found in %BUILD_DIR%%COL_RESET%
)

echo.
echo ===== ALL DONE =====
pause
