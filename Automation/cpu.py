import psutil
import time
from colorama import Fore, Style, init

# Initialize colorama
init(autoreset=True)

def monitorize_components():
    while True:
        cpu_percent = psutil.cpu_percent(interval=1)
        ram_percent = psutil.virtual_memory().percent

        # Define color based on usage thresholds
        cpu_color = (
            Fore.GREEN if cpu_percent < 50 else (Fore.YELLOW if cpu_percent <= 75 else Fore.RED)
        )
        ram_color = (
            Fore.GREEN if ram_percent < 50 else (Fore.YELLOW if ram_percent <= 75 else Fore.RED)
        )

        # Print CPU Usage with color
        print(f"CPU Usage: {cpu_color}{cpu_percent}%{Style.RESET_ALL}")

        # Print RAM Usage with color
        print(f"RAM Usage: {ram_color}{ram_percent}%{Style.RESET_ALL}")

        time.sleep(1)

monitorize_components()
