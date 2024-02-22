import socket
import re
import paramiko

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

def create_ssh_connection(host, username, password):
    """Create an SSH connection using paramiko."""
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(host, username=username, password=password)
    return ssh

if __name__ == "__main__":
    local_ip = get_local_ip()
    ssh_logs_file = "/var/log/auth.log"  # Adjust the path based on your system
    target_ip = "127.0.0.1"  # Replace with the target IP address
    ssh_host = "192.168.1.229"  # Replace with the SSH host
    ssh_username = "Bogdan"  # Replace with the SSH username
    ssh_password = "1234"  # Replace with the SSH password

    if check_ssh_logs(ssh_logs_file, local_ip):
        print(f"Your IP ({local_ip}) is present in SSH logs.")

        # Create an SSH connection and compare IPs
        ssh = create_ssh_connection(ssh_host, ssh_username, ssh_password)
        stdin, stdout, stderr = ssh.exec_command('hostname -I')
        remote_ip = stdout.read().decode().strip()

        if local_ip == remote_ip:
            print("Local and remote IPs match.")
        else:
            print("Local and remote IPs do not match.")

        ssh.close()
    else:
        print(f"Your IP ({local_ip}) is not found in SSH logs.")
