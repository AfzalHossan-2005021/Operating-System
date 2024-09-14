#!/bin/bash

# Check if the file exists
if [ ! -f $2 ]; then
    echo "File does not exist: $2"
    exit 1
fi

# Check if the file is readable 
if [ ! -r $2 ]; then
    echo "File is not readable: $2"
    exit 1
fi

# Convert the input_file to unix format
dos2unix -q $2

# Create an array to store the lines
input_file=()
# Read each line into the array
while IFS= read -r line; do
    input_file+=("$line")  # Append each line to the array
done < "$2"
