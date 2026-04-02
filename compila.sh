#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
CONFIG="${1:-Debug}"
BUILD_DIR="$SCRIPT_DIR/build/linux-debug"

echo "===== CONFIGURAZIONE BUILD LINUX ($CONFIG) ====="
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CONFIG"

echo "===== COMPILAZIONE ====="
cmake --build "$BUILD_DIR" --config "$CONFIG"

EXECUTABLE="$BUILD_DIR/GraviCLI"
if [[ -f "$BUILD_DIR/$CONFIG/GraviCLI" ]]; then
	EXECUTABLE="$BUILD_DIR/$CONFIG/GraviCLI"
fi

echo "===== AVVIO PROGRAMMA ($EXECUTABLE) ====="
"$EXECUTABLE"
