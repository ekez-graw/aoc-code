#!/bin/bash

export AOC_DATA_PATH="/home/dad/src/aoc/aoc-data/2024/"

purge=false

if [ "$1" == "--purge" ]; then
	purge=true
	shift
fi

folder=$1

if $purge; then
	rm -rf _build
fi

build_folder() {
	local folder=$1
	mkdir -p _build/$folder
	cd _build/$folder
	echo "Building in folder: $(pwd)"
	cmake -DTARGET_DIR=$folder ../..
	make
	cd ../..
}

echo "Current path: $(pwd)"
echo "AOC_DATA_PATH: $AOC_DATA_PATH"

if [ -z "$folder" ]; then
	for dir in [0-9]*; do
		if [ -d "$dir" ]; then
			build_folder "$dir"
		fi
	done
else
	build_folder "$folder"
fi
