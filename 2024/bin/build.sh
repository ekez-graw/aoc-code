#!/bin/bash

rm -rf _build

build_folder() {
	local folder=$1
	mkdir -p _build/$folder
	cd _build/$folder
	cmake ../../
	make
	cd ../..
}

if [ -z "$1" ]; then
	for folder in $(ls -d */); do
		folder_name=$(basename $folder)
		build_folder $folder_name
	done
else
	build_folder $1
fi
