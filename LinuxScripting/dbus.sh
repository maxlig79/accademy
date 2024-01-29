#!/bin/bash

while true; do
    # Get the PowerSupply object path
    power_supply_path=$(upower -e | grep 'battery')

    if [ -n "$power_supply_path" ]; then
        # Get the battery status using the PowerSupply object path
        battery_status=$(upower -i $power_supply_path | grep "state:" | awk '{print $2}')

        if [ "$battery_status" == "charging" ] || [ "$battery_status" == "fully-charged" ]; then
            echo "This machine is currently plugged in."
        elif [ "$battery_status" == "discharging" ]; then
            echo "This machine is currently using the battery."
        else
            echo "Error: Unable to determine charging status."
        fi
    else
        echo "Error: No battery found."
    fi

    # Wait for a few seconds before checking again
    sleep 5
done
