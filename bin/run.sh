#!/bin/bash

if [ -z "$AOC_DATA_PATH" ]; then
	echo "AOC_DATA_PATH environment variable is not set."
	exit 1
fi

run_folder() {
	local folder=$1
	first_folder=$(echo $folder | cut -d'/' -f1)
	second_folder=$(echo $folder | cut -d'/' -f2)
	if [ -z "$2" ]; then
		INPUT_FILE=$AOC_DATA_PATH/"$first_folder/p$second_folder-input.txt"
	elif [ "$2" == "example" ]; then
		INPUT_FILE=$AOC_DATA_PATH/"$first_folder/p$second_folder-example-input.txt"
	else
		echo "Invalid input argument: $2"
		exit 1
	fi
	cd _build
	$(pwd)/$folder/p$second_folder --input-file $INPUT_FILE
}

if [ -z "$1" ]; then
	for folder in $(ls -d */); do
		folder_name=$(basename $folder)
		run_folder $folder_name $2
	done
else
	run_folder $1 $2
fi
