#!/usr/bin/env python3.12

import os, uuid
from jinja2 import Environment, FileSystemLoader

def create_project(day, part, output_path):
    day_folder = os.path.join(output_path, f"Day{day:02}_{part}")
    if os.path.exists(day_folder):
        print(f"{day_folder} already exists.")
        return
    properties_folder = os.path.join(day_folder, "Properties")
    csproj_file = os.path.join(day_folder, f"Day{day:02}_{part}.csproj")
    program_file = os.path.join(day_folder, "Program.cs")
    json_file = os.path.join(properties_folder, "launchSettings.json")
    input_file = os.path.join(day_folder, "input.txt")

    os.makedirs(day_folder, exist_ok=True)
    os.makedirs(properties_folder, exist_ok=True)

    env = Environment(loader=FileSystemLoader('src'))
    csproj_template = env.get_template(".csprojtemplate")
    program_template = env.get_template("program.cstemplate")
    json_template = env.get_template("SystemLoader.json")
    with open(csproj_file, 'w') as f:
        f.write(csproj_template.render(day_folder=day_folder))
    with open(program_file, 'w') as f:
        f.write(program_template.render(day=day, part=part))
    with open(json_file, 'w') as f:
        f.write(json_template.render())
    if not os.path.exists(input_file):
            open(input_file, 'w').close()

    add_project_to_solution(f"Day{day:02}_{part}")

    print(f"Project setup complete for Day {day:02} Part {part}")

def add_project_to_solution(project_name):
    sln_path = "/home/kai/RiderProjects/AoC_2024/AoC_2024.sln"
    solution_guid = "{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}"
    project_guid = f"{{{uuid.uuid4()}}}"

    # Read the existing solution file
    with open(sln_path, 'r+') as sln_file:
        lines = sln_file.readlines()

        # Check if the project already exists
        for line in lines:
            if project_name in line:
                print(f"Project '{project_name}' already exists in the solution.")
                return

        # Find the index to insert the new project before the global section
        insert_index = 0
        for index, line in enumerate(lines):
            if line.strip() == "Global":
                insert_index = index
                break

        # Insert the new project declaration
        new_project_declaration = f'Project("{solution_guid}") = "{project_name}", "{project_name}\\{project_name}.csproj", "{project_guid}"\nEndProject\n'
        lines.insert(insert_index, new_project_declaration)

        # Prepare the new project's configurations for the Global section
        project_configurations = (
            f'\t\t{project_guid}.Debug|Any CPU.ActiveCfg = Debug|Any CPU\n'
            f'\t\t{project_guid}.Debug|Any CPU.Build.0 = Debug|Any CPU\n'
            f'\t\t{project_guid}.Release|Any CPU.ActiveCfg = Release|Any CPU\n'
            f'\t\t{project_guid}.Release|Any CPU.Build.0 = Release|Any CPU\n'
        )

        # Find the EndGlobal section to insert project configurations
        global_section_index = lines.index("\tEndGlobalSection\n")  # Locate the first EndGlobal
        end_global_index = lines.index("\tEndGlobalSection\n", global_section_index + 1)  # Locate the second EndGlobal

        # Insert the configurations before the second EndGlobal
        lines.insert(end_global_index, project_configurations)

        # Write back the modified lines to the solution file
        sln_file.seek(0)
        sln_file.writelines(lines)
        sln_file.truncate()  # Truncate the file to remove any old content beyond the new size

    print(f"Added project '{project_name}' to solution '{sln_path}'.")


# Main Script
try:
    day = int(input("Enter the day number you want to set up (1-24): "))
    output_path = "/home/kai/RiderProjects/AoC_2024"  # Default path to Advent of Code project folder
    if not 1 <= day <= 24: raise ValueError
    create_project(day, 1, output_path)
    create_project(day, 2, output_path)
except Exception as e:
    print(f"An unexpected error occurred: {e}")