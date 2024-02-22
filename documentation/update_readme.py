"""
@brief This script updates relative paths in README.md to corrected relative paths
"""

import os
import re


def update_readme():
    """
    @brief Update relative paths in README.md to corrected relative paths

    This function reads the README.md file, finds all relative paths in markdown links and img src,
    replaces them with corrected relative paths
    """
    # Define the base URL where your project is hosted
    base_url = "../../../"

    # Get the directory of the current script
    script_dir = os.path.dirname(os.path.realpath(__file__))

    # Open the README file and read its contents
    with open(os.path.join(script_dir, "../README.md"), "r") as file:
        readme = file.read()

    readme = re.sub(r"\]\(\./", "](" + base_url, readme)

    readme = re.sub(r"src=\"\./", 'src="' + base_url, readme)
    readme = re.sub(r"href=\"\./", 'href="' + base_url, readme)

    # Write the result to a new file
    with open(os.path.join(script_dir, "README.md"), "w") as file:
        file.write(readme)


if __name__ == "__main__":
    update_readme()
