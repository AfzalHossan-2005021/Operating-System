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
