# Check if the required files exist
if [ ! -e "bashcrc" ] || [ ! -e "bashcrc.txt" ]; then
    echo "Error: One or both of the files 'bashcrc' and 'bashcrc.txt' not found."
    exit 1
fi

# Fields to search and replace
fields=("ARTIFACTORY_API_KEY" "ARTIFACTORY_USER" "ANDROID_HOME" "JAVA_HOME" "IVI_ADB_SERIAL")

# Iterate through each field
for field in "${fields[@]}"; do
    # Search for the field in bashcrc.txt and get its value
    value=$(grep "$field" bashcrc.txt | awk -F'=' '{print $2}')

    # Check if the value is not empty
    if [ -n "$value" ]; then
        # Replace the value in bashcrc
        sed -i "s/$field=.*/$field=$value/" bashcrc
        echo "Replaced $field with value from bashcrc.txt."
    else
        echo "Error: $field not found in bashcrc.txt or value is empty."
    fi
done

echo "Search and replace completed."
