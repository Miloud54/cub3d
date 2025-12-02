#!/usr/bin/env bash
set -euo pipefail


BIN=${1:-./cub3D}
MAP=${2:-maps/valid/map1.cub}


if [ ! -x "$BIN" ]; then
	echo "Binaire introuvable: $BIN" >&2
	exit 2
fi
if [ ! -f "$MAP" ]; then
	echo "Map introuvable: $MAP" >&2
	exit 2
fi


# Exécution courte pour ne pas bloquer la CI
( "$BIN" "$MAP" & pid=$!; sleep 2; kill $pid >/dev/null 2>&1 || true )