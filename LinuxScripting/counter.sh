#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Assign the filename from the command line argument
filename=$1

# Check if the file exists
if [ ! -e "$filename" ]; then
    echo "Error: File $filename not found."
    exit 1
fi

# Count occurrences of the specified string in the file
occurrences=$(grep -o -c "StrictHostKeyChecking" "$filename")

# Display the result
echo "Occurrences of 'StrictHostKeyChecking' in $filename: $occurrences"
