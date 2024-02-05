import subprocess
class Linux:

    def __init__(self, filename,destination):
        self.filename = filename
        self.destination = destination
        
    def list_items(self):
        try:
            # Using subprocess.run to execute the "ls" command
            result = subprocess.run(["ls", "-l"], capture_output=True, text=True, check=True)

            # Print the output of the command
            print(result.stdout)

        except subprocess.CalledProcessError as e:
            print("Error:", e)

    def remove_item(self):
        try:
            subprocess.run(['rm', self.filename])
            print(f"File '{self.filename}' deleted successfully.")
        except Exception as e:
            print(f"Error executing rm command: {e}")

    def create_file(self):
        try:
            subprocess.run(['touch', self.filename])
            print(f"File '{self.filename}' created successfully.")
        except Exception as e:
            print(f"Error executing touch command: {e}")

    def move_file(self):
        try:
            subprocess.run(['mv', self.filename, self.destination_filename])
            print(f"File '{self.filename}' moved to '{self.destination_filename}' successfully.")
        except Exception as e:
            print(f"Error executing mv command: {e}")

    def copy_file(self):
        try:
            subprocess.run(['cp', self.filename, self.destination_filename])
            print(f"File '{self.filename}' copied to '{self.destination_filename}' successfully.")
        except Exception as e:
            print(f"Error executing cp command: {e}")

        
if __name__ == "__main__":
    # Ask user what command wants to use
    user_command=input("What command do you want to execute:").lower()

    # Call the list_items method to execute the 'ls' command
    if(user_command=='ls'):
        nume_fisier=''
        destinatie_fisier=''
        command_executor = Linux(nume_fisier,destinatie_fisier)
        output = command_executor.list_items()

    # Call the create_file method to execute the 'touch' command
    elif(user_command=='touch'):
        nume_fisier=input("What file do you want to create ").lower()
        destinatie_fisier=''
        command_executor = Linux(nume_fisier,destinatie_fisier)
        output = command_executor.create_file()

     # Call the remove_item method to execute the 'rm' command
    elif(user_command=='rm'):
        nume_fisier=input("What file do you want to delete").lower()
        destinatie_fisier=''
        command_executor = Linux(nume_fisier,destinatie_fisier)
        output = command_executor.remove_item()

     # Call the move_file method to execute the 'mv' command
    elif(user_command=='mv'):
        nume_fisier=input("What file do you want to move").lower()
        destinatie_fisier=("Write the path:")
        command_executor = Linux(nume_fisier,destinatie_fisier)
        output = command_executor.move_file()

     # Call the copy_file method to execute the 'cp' command
    elif(user_command=='cp'):
        nume_fisier=input("What file do you want to copy").lower()
        destinatie_fisier=("Write the path:")
        command_executor = Linux(nume_fisier,destinatie_fisier)
        output = command_executor.copy_file()

    else:
       output="Command doesn't exist"

    # Print the result
    print(output)
