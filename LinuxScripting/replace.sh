#!/bin/bash

# Set the file path
file="log.txt"

# Set the word to replace
new_word="AUTOMATION"

# Set the log file path
log_file="replace_log.txt"

# Loop through the specified lines
for line_num in {63..69}; do
    # Get the 6th word from the line
    word=$(awk -v line=$line_num '{if (NR==line) print $6}' $file)

    # Replace the word in the line
    sed -i "${line_num}s/$word/$new_word/" $file

    # Print the replacement message to the log file with each letter on a new line
    echo "$word was replaced with the letters:" >> $log_file
    for ((i=0; i<${#new_word}; i++)); do
        echo "${new_word:i:1}" >> $log_file
    done

    echo "" >> $log_file  # Add an empty line between replacements
done

