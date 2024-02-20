import os

def create_directory(path):
    """
    Create a directory at the specified path if it doesn't exist.

    Parameters:
    - path (str): The path of the directory to be created.
    """
    if not os.path.exists(path):
        os.makedirs(path)
        os.chmod(path, 0o777)
    else:
        print(f'Directory {path} already exists!')

def create_file(file_path):
    """
    Create an empty file at the specified path if it doesn't exist.

    Parameters:
    - file_path (str): The path of the file to be created.
    """
    with open(file_path, 'w') as file:
        file.write(' ')
        os.chmod(file_path, 0o777)

def create_structure():
    """
    Create a predefined directory structure for a project.
    """
    base_directory = '/home/projectx/Desktop/WeekAutomation'
    create_directory(base_directory)

    main_directory = os.path.join(base_directory, 'main')
    create_directory(main_directory)

    head_directory = os.path.join(main_directory, 'HEAD')
    create_directory(head_directory)

    commit_directory = os.path.join(main_directory, 'commit')
    create_directory(commit_directory)

    dev_directory = os.path.join(head_directory, 'dev')
    create_directory(dev_directory)

    readme_file = os.path.join(head_directory, 'readme.md')
    create_file(readme_file)

    systemd_file = os.path.join(dev_directory, 'systemd.d')
    create_file(systemd_file)

    opt_directory = os.path.join(dev_directory, 'Opt')
    create_directory(opt_directory)

    commitfix_directory = os.path.join(commit_directory, 'commit_fiX')
    create_directory(commitfix_directory)

    variables_file = os.path.join(commit_directory, 'variables.txt')
    create_file(variables_file)

    commitfix_file = os.path.join(commitfix_directory, 'commit_fiX_FIX')
    create_file(commitfix_file)

    src_directory = os.path.join(commitfix_directory, 'src')
    create_directory(src_directory)

    unittest_file = os.path.join(src_directory, 'unit_test.py')
    create_file(unittest_file)

    app_main_directory = os.path.join(src_directory, 'app_main')
    create_directory(app_main_directory)

def rename_function(structure):
    """
    Rename directories and files within a given directory structure
    by capitalizing the first and last characters.

    Parameters:
    - structure (str): The path of the directory structure to be renamed.
    """
    main_director = os.path.basename(structure)
    new_main_dir = main_director[0].upper() + main_director[1:-1].lower() + main_director[-1].upper()
    os.rename(structure, os.path.join(os.path.dirname(structure), new_main_dir))

    # Recursively rename directories and files
    for root, dirs, files in os.walk(os.path.join(os.path.dirname(structure), new_main_dir)):
        for name in dirs + files:
            old_path = os.path.join(root, name)
            new_name = name[0].upper() + name[1:-1].lower() + name[-1].upper()
            new_path = os.path.join(root, new_name)
            os.rename(old_path, new_path)

            if os.path.isdir(new_path):
                rename_function(new_path)

if __name__ == "__main__":
    create_structure()
    structure_path = '/home/projectx/Desktop/WeekAutomation/main'
    rename_function(structure_path)
