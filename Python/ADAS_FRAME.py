import json

def parse_payload(payload):
    """
    Parse the payload and extract PDUs.

    Parameters:
    - payload (list): List of hexadecimal strings representing the payload.

    Returns:
    - list: List of extracted PDUs.
    """
    return [payload[i+4:i+12] for i in range(0, len(payload), 12) if i + 12 < len(payload) and payload[i] == '00']

def hex_to_bin(hex_strings):
    """
    Convert a list of hexadecimal strings to a binary string.

    Parameters:
    - hex_strings (list): List of hexadecimal strings.

    Returns:
    - str: Binary string.
    """
    bin_string = ''

    for hex_string in hex_strings:
        bin_string += bin(int(hex_string, 16))[2:].zfill(8)
    return bin_string.strip()

def bin_to_hex(bin_string):
    """
    Convert a binary string to hexadecimal.

    Parameters:
    - bin_string (str): Binary string.

    Returns:
    - str: Hexadecimal string.
    """
    return hex(int(bin_string, 2))[2:]

def change_values(bin_payload, signal):
    """
    Change the values of a signal in the binary payload.

    Parameters:
    - bin_payload (str): Binary payload.
    - signal (dict): Dictionary containing signal information.

    Returns:
    - str: Updated binary payload.
    """
    byte_pos = signal['BytePos']
    current_byte = bin_payload[8 * byte_pos: 8 * byte_pos + 8]
    bit_pos = signal['BitPos']
    size = signal['Size']
    selected_byte = current_byte[7 - bit_pos:]
    selected_byte = selected_byte[:size]
    value = signal['Value']
    bin_conversion = format(value, '0{}b'.format(size))

    # Modify the bin_payload by replacing the relevant part with the new value
    new_value = current_byte[:7 - bit_pos] + bin_conversion + current_byte[7 - bit_pos + size:]
    bin_payload = bin_payload[:8 * byte_pos] + new_value + bin_payload[8 * byte_pos + 8:]

    return bin_payload

# Load signals from a JSON file
with open('signals_adas.json', 'r') as file:
    signals = json.load(file)

payload1 = [
        '00', '06', '02', '08', '80', '00', '00', '00', '00', '00', '00', '00', '00', '05', 'D0', '08',
        'FF', '60', '00', '00', '02', '00', '00', '00', '00', '06', '01', '08', '80', '00', '00', '00',
        '00', '00', '00', '00', '00', '00', '10', 'C7', '77', '8A', '70', 'AB', 'AF', '88', '2A', '8C'
    ]
payload2 = [
        '00', '06', '02', '08', '40', '00', '00', '10', '00', '00', '00', '00', '00', '05', 'D0', '08',
        '21', '20', '00', '00', '02', '00', '00', '00', '00', '06', '01', '08', '80', '00', '00', '00',
        '00', '00', '00', '00', '00', '00', '00', '11', '29', 'FB', '84', '33', '1D', 'E5', '5E', '9D'
    ]

# Parse payload to extract signals
parsed_PDUs = parse_payload(payload1)

print("Payload1")
# Iterate for each extracted PDU and corresponding signal
for bin_payload, signal_name in zip(parsed_PDUs, signals.keys()):
    print(f"Processing signal: {signal_name}")
    bin_payload = hex_to_bin(bin_payload)
    print("Binary payload is", bin_payload)
    bin_payload = change_values(bin_payload, signals[signal_name])

parsed_PDUs = parse_payload(payload2)

print("Payload2")
# Iterate for each extracted PDU and corresponding signal
for bin_payload, signal_name in zip(parsed_PDUs, signals.keys()):
    print(f"Processing signal: {signal_name}")
    bin_payload = hex_to_bin(bin_payload)
    print("Binary payload is", bin_payload)
    bin_payload = change_values(bin_payload, signals[signal_name])
