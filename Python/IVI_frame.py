import json

def extract_value(frame, signal):
    """
    Extract the value of the given signal based on the byte position,
    start of signal, and length (in bits).

    Args:
        frame (list of hex numbers): Frame from which to extract the value of the signal.
        signal (dictionary): Signal to be processed, containing information about
                             the byte position in the frame, size of signal, and
                             start position inside the byte.

    Returns:
        int: The extracted value of the signal.
    """
    byte_position = signal['BytePos']
    bit_position = signal['BitPos']
    size = signal['Size']
    # Combine bytes to get the value
    value = 0
    for i in range(size):
        value |= (frame[byte_position] >> (bit_position - i)) & 1
        if i < size - 1:
            value <<= 1

    return value

# Load signals from a JSON file
with open('signals.json', 'r') as file:
    signals = json.load(file)

# Define frames as a dictionary in a string
frames_str = """
{
    'IVI_frame_1': [0x60, 0x20, 0x45, 0x6C, 0xFE, 0x3D, 0x4B, 0xAA],
    'IVI_frame_2': [0x40, 0x12, 0x6C, 0xAF, 0x05, 0x78, 0x4A, 0x04]
}
"""

# Load frames from the string
frames = eval(frames_str)

if __name__ == "__main__":
    for frame_name, frame in frames.items():
        print(f"Values for {frame_name}:")
        for signal_name, signal_info in signals.items():
            value = extract_value(frame, signal_info)
            print(f"{signal_name}: {value}")
