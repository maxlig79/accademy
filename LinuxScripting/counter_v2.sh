#!/bin/bash

# Check if at least one filename is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <filename1> [<filename2> ...]"
    exit 1
fi

# Iterate through each provided filename
for filename in "$@"; do
    # Check if the file exists
    if [ ! -e "$filename" ]; then
        echo "Error: File $filename not found."
        continue
    fi

    # Use grep to find occurrences and display line numbers
    echo "Occurrences of 'StrictHostKeyChecking' in $filename:"
    grep -n "StrictHostKeyChecking" "$filename"
    echo
done
