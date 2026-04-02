@echo off
setlocal EnableDelayedExpansion
REM Script per configurare, compilare e avviare GraviCLI su Windows

set "SCRIPT_DIR=%~dp0"
set "CONFIG=Debug"
if not "%~1"=="" set "CONFIG=%~1"

REM Rimuovi il backslash finale da SCRIPT_DIR se presente
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"
set "BUILD_DIR=%SCRIPT_DIR%\build\windows-debug"

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
    echo Avvio dell'eseguibile...
    echo.

    set "EXE_PATH=%BUILD_DIR%\%CONFIG%\GraviCLI.exe"
    if not exist "!EXE_PATH!" set "EXE_PATH=%BUILD_DIR%\GraviCLI.exe"

    if exist "!EXE_PATH!" (
        "!EXE_PATH!"
    ) else (
        echo Eseguibile non trovato: !EXE_PATH!
        pause
        exit /b 1
    )
) else (
    echo.
    echo ===== ERRORE NELLA COMPILAZIONE =====
    echo.
    pause
    exit /b 1
)

pause
endlocal
