#!/bin/bash

# Set the current folder as the target folder 
target_folder=$(pwd)

# Build directory name
build_dir="build"

# Check if build directory exists
if [ ! -d "$target_folder/$build_dir" ]; then

  # Build directory does not exist, create it
  echo "Creating $build_dir directory."  
  mkdir "$target_folder/$build_dir"
else
  # Build directory already exists
  echo "$build_dir exists."
fi

cd $target_folder/$build_dir
cmake ..
make
cd ..
dials.python main.py