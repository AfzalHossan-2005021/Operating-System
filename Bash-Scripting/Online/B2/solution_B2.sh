#!/bin/bash

# Install the tree package to visualize the directory structure with this command: sudo apt install tree

# This script will take a file as an argument and will print the number of lines in the file.
if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

filename=$1
if [ ! -f "$filename" ]; then
  echo "Error: File '$filename' not found."
  exit 1
fi

main_dir="Academic Materials"

mkdir -p "$main_dir"

while IFS= read -r line; do
    course_name=$(echo "$line" | cut -d' ' -f1-2)
    course_code=$(echo "$course_name" | cut -d' ' -f2)
    level=$(echo "$course_code" | cut -d' ' -f2| cut -c1)
    term=$(echo $line | cut -d' ' -f3 | cut -d'-' -f2)
    if [ $(($course_code % 2)) -eq 0 ]; then
        course_dir="$main_dir/L${level}T${term}/LABS/$course_name"
    else
        course_dir="$main_dir/L${level}T${term}/$course_name"
    fi
    mkdir -p "$course_dir"
done < "$filename"

if ! which tree > /dev/null 2>&1; then
    echo "Error: tree command not found."
    exit 1
fi

tree "$main_dir"