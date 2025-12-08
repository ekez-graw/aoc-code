#!/bin/bash
set -euo pipefail

purge=false
if [ "${1:-}" = "--purge" ]; then
  purge=true
  shift
fi

# strip trailing slash
folder="${1:-}"
folder="${folder%/}"

if $purge; then
  rm -rf _build
fi

build_folder() {
  local folder="$1"
  local safe builddir

  if [ -z "$folder" ]; then
    safe="root"
  else
    safe="$(printf '%s' "$folder" | sed 's#/#_#g' | sed 's#^_##')"
  fi

  builddir="_build/${safe}"
  mkdir -p "$builddir"
  echo "Building target: ${folder:-<all>}"
  echo "Build dir: $(realpath "$builddir")"

  if [ -z "$folder" ]; then
    cmake -S . -B "$builddir"
  elif [[ "$folder" == */* ]]; then
    # nested path (year/day) -> validate and pass TARGET_DIR
    if [ ! -d "$folder" ] || [ ! -f "$folder/CMakeLists.txt" ]; then
      echo "Requested nested target '$folder' not found or missing CMakeLists.txt" >&2
      exit 1
    fi
    cmake -S . -B "$builddir" -DTARGET_DIR="$folder"
  else
    # plain year -> configure from repo root so the year's CMakeLists builds all days
    if [ ! -d "$folder" ] || [ ! -f "$folder/CMakeLists.txt" ]; then
      echo "Requested year '$folder' not found or missing CMakeLists.txt" >&2
      exit 1
    fi
    cmake -S . -B "$builddir"
  fi

  cmake --build "$builddir" -- -j
}

echo "Current path: $(pwd)"

if [ -z "$folder" ]; then
  for dir in [0-9]*; do
    if [ -d "$dir" ] && [ -f "$dir/CMakeLists.txt" ]; then
      build_folder "$dir"
    else
      echo "Skipping $dir (no CMakeLists.txt)"
    fi
  done
else
  build_folder "$folder"
fi
