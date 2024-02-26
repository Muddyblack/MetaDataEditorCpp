## @package run_ress_gen
#  @brief This script contains the ResourceGenerator class
#         Which is used to generate the QT resources file for a project.
#  @author Muddyblack
#  @date 21.02.2024
import os
import subprocess
from typing import List, Optional


class ResourceGenerator:
    """@brief A class used to generate resources for a project.

    @details This class provides methods to run a resource generation script and generate resources for a project.

    @param script_dir The directory where the script is located.
    @param script_path The path to the script that generates the resources.
    @param resource_file The path to the resource file.
    """

    def __init__(self, script_dir: str):
        self.script_dir = script_dir
        self.script_path = os.path.join(script_dir, "resources_gen.py")
        self.resource_file = os.path.join(script_dir, "resources.qrc")

    def run_generate_qrc(
        self,
        paths: List[str],
        output_file: str,
        overwrite: bool = False,
        prefix: Optional[str] = None,
    ):
        """@brief Runs the resource generation script with the given arguments.

        @param paths The paths to the resources.
        @param output_file The path to the output file.
        @param overwrite Whether to overwrite the output file (default is False).
        @param prefix The prefix to use for the resources (default is None).
        """
        if not paths:
            raise ValueError("Paths cannot be empty")

        command = ["python", self.script_path] + paths + [output_file]
        if overwrite:
            command.append("--overwrite")
        if prefix:
            command.extend(["--prefix", prefix])

        subprocess.run(command, check=True)

    def generate_resources(self):
        """@brief Hard coded function which generates the resources for the project."""
        print("Generating resources.qrc")
        self.run_generate_qrc(
            paths=[os.path.join(self.script_dir, "styles")],
            output_file=self.resource_file,
            overwrite=True,
        )

        self.run_generate_qrc(
            paths=[
                os.path.join(self.script_dir, "resources"),
                os.path.join(self.script_dir, "app.ico"),
            ],
            output_file=self.resource_file,
            overwrite=False,
        )


if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.realpath(__file__))
    generator = ResourceGenerator(script_dir)

    generator.generate_resources()
