#!/bin/bash

# Check if all required arguments are provided
if [ $# -ne 3 ]; then
  echo "Usage: $0 <log_file> <access_type> <time_range>"
  exit 1
fi

log_file=$1
access_type=$2
time_range=$3

# Extract start and end times
startHH=$(echo $time_range | cut -d'-' -f1)
endHH=$(echo $time_range | cut -d'-' -f2)

# Ensure that numbers with leading zeroes are treated as decimal
startHH=$((10#$startHH))
endHH=$((10#$endHH))

# Temporary file to store usernames
tmp_file=$(mktemp)

# Loop through the time range and filter logs for each hour in the range
while IFS= read -r line; do
    HH=$(echo $line | cut -d' ' -f2 | cut -d':' -f1)
    HH=$((10#$HH))
    TYPE=$(echo $line | cut -d' ' -f4-)
    if [ "$TYPE" = "$access_type" ] && [ $HH -ge $startHH ] && [ $HH -le $endHH ]; then
        echo $line >> "$tmp_file"
    fi
done < "$log_file"

# Extract usernames and count the number of times each username appears
cut -d' ' -f3 < "$tmp_file" | sort | uniq -c | sort -rn

# Clean up temporary file
rm "$tmp_file"
