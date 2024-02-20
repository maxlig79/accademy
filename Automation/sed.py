import re

def replace_timestamp(line, line_number):
    """Replace timestamp with the last number if either of the last two words is exclusively a number."""
    words = line.split()
    last_two_words = words[-2:]

    if all(word.isdigit() for word in last_two_words):
        new_timestamp = last_two_words[-1]
        updated_line = re.sub(r'\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}', new_timestamp, line)
        print(f"Line {line_number}: Timestamp replaced - Original: {line.strip()}, Updated: {updated_line.strip()}")
        return updated_line
    else:
        return line

if __name__ == "__main__":
    input_log_file = "log.txt"
    output_log_file = "updated_log.txt"

    with open(input_log_file, 'r') as infile, open(output_log_file, 'w') as outfile:
        for line_number, line in enumerate(infile, start=1):
            updated_line = replace_timestamp(line, line_number)
            outfile.write(updated_line)

    print(f"Updated log file created: {output_log_file}")
