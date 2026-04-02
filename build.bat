@echo off
setlocal
REM Script per configurare e compilare GraviCLI su Windows

set "SCRIPT_DIR=%~dp0"
set "CONFIG=Debug"
if not "%~1"=="" set "CONFIG=%~1"
set "BUILD_DIR=%SCRIPT_DIR%build\windows-debug"

REM Rimuovi il backslash finale da SCRIPT_DIR se presente
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

echo.
echo ===== CONFIGURAZIONE BUILD WINDOWS (%CONFIG%) =====
echo.

cmake -S "%SCRIPT_DIR%" -B "%BUILD_DIR%"

if %errorlevel% neq 0 (
    echo.
    echo ===== ERRORE NELLA CONFIGURAZIONE =====
    echo.
    pause
    exit /b 1
)

echo.
echo ===== COMPILAZIONE =====
echo.
cmake --build "%BUILD_DIR%" --config %CONFIG%

REM Controlla se la compilazione è riuscita
if %errorlevel% equ 0 (
    echo.
    echo ===== COMPILAZIONE RIUSCITA =====
    echo.
) else (
    echo.
    echo ===== ERRORE NELLA COMPILAZIONE =====
    echo.
)

pause
endlocal
