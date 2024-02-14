def calculate_range(battery_level):
    """
    Calculate the estimated range of an electric vehicle based on the battery level.

    Parameters:
    - battery_level (float): Current battery level in percentage.

    Returns:
    - float: Estimated range in kilometers.
    """
    # Constants
    total_battery_capacity = 62  # in kWh
    energy_consumption = 15.6  # in kWh/100km

    # Calculate available energy based on battery level
    available_energy = total_battery_capacity * (battery_level / 100)

    # Calculate estimated range
    estimated_range = available_energy / (energy_consumption / 100)

    return estimated_range

if __name__ == "__main__":
    # Get battery level from user input
    battery_level = float(input("Enter the current battery level in percentage: "))

    # Check if battery level is within valid range (0-100)
    if 0 <= battery_level <= 100:
        # Calculate and display the estimated range
        range_result = calculate_range(battery_level)
        print(f"Estimated available range: {range_result:.2f} km")
    else:
        print("Invalid battery level. Please enter a value between 0 and 100.")
