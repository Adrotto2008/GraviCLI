#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
CONFIG="${1:-Debug}"
UNAME_S="$(uname -s)"
case "$UNAME_S" in
	Linux)
		BUILD_PLATFORM="linux"
		BUILD_PLATFORM_LABEL="LINUX"
		;;
	Darwin)
		BUILD_PLATFORM="macos"
		BUILD_PLATFORM_LABEL="MACOS"
		;;
	MINGW*|MSYS*|CYGWIN*)
		BUILD_PLATFORM="windows"
		BUILD_PLATFORM_LABEL="WINDOWS"
		;;
	*)
		BUILD_PLATFORM="unknown"
		BUILD_PLATFORM_LABEL="UNKNOWN"
		;;
esac

BUILD_DIR="$SCRIPT_DIR/build/${BUILD_PLATFORM}-debug"

echo "===== CONFIGURAZIONE BUILD ${BUILD_PLATFORM_LABEL} ($CONFIG) ====="
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CONFIG"

echo "===== COMPILAZIONE ====="
cmake --build "$BUILD_DIR" --config "$CONFIG"

EXECUTABLE="$BUILD_DIR/GraviCLI"
if [[ -f "$BUILD_DIR/$CONFIG/GraviCLI" ]]; then
  EXECUTABLE="$BUILD_DIR/$CONFIG/GraviCLI"
elif [[ -f "$BUILD_DIR/GraviCLI.exe" ]]; then
  EXECUTABLE="$BUILD_DIR/GraviCLI.exe"
fi

echo "===== AVVIO PROGRAMMA ($EXECUTABLE) ====="
"$EXECUTABLE"
