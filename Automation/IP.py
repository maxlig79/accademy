import socket
import re

def get_local_ip():
    """Extract local IP using socket library methods"""
    return socket.gethostbyname(socket.gethostname())

def check_ssh_logs(log_file, target_ip):
    """Check if the target IP is present in SSH logs."""
    with open(log_file, 'r') as file:
        logs = file.read()

    ip_pattern = re.compile(r'\b(?:\d{1,3}\.){3}\d{1,3}\b')  # IP address pattern

    # Extract all IP addresses from logs
    all_ips = re.findall(ip_pattern, logs)

    return target_ip in all_ips

if __name__ == "__main__":
    local_ip = get_local_ip()
    ssh_logs_file = "/var/log/auth.log"  # Adjust the path based on your system

    if check_ssh_logs(ssh_logs_file, local_ip):
        print(f"Your IP ({local_ip}) is present in SSH logs.")
    else:
        print(f"Your IP ({local_ip}) is not found in SSH logs.")
