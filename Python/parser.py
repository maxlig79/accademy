import re

def extract_last_word_between_timestamps(file_path, start_timestamp, end_timestamp,output_file_path):
    result = []

    with open(file_path, 'r') as file:
        for line in file:
            timestamp_match = re.search(r'(\d{2}:\d{2}:\d{2}\.\d{3})', line)

            if timestamp_match:
                current_timestamp = timestamp_match.group(1)

                if start_timestamp <= current_timestamp <= end_timestamp:
                    words = line.split()
                    if words:
                        result.append(words[-1].strip())  # Remove leading/trailing whitespaces

    with open(output_file_path, 'w') as file:
        for words in result:
            file.write(words + '\n')

    print('The .txt file have successfully saved')

    return result

# Example usage
file_path = 'logcat_applications.txt'
start_timestamp = "17:56:07.996"
end_timestamp = "17:56:08.357"
output_file_path="result.txt"
result = extract_last_word_between_timestamps(file_path, start_timestamp, end_timestamp,output_file_path)
print(result)








