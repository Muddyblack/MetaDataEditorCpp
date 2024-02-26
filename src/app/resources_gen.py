## @package resources_gen
#  @brief This script contains the QrcGenerator class which is used to generate Qt resource files.
#  @author Muddyblack
#  @date 21.02.2024
import os
import argparse
from typing import List, Optional


class QrcGenerator:
    """@brief A class used to generate Qt resource files.

    @param output_dir The directory where the output file is located.
    @param current_prefix The current prefix used in the resource file.
    """

    def __init__(
        self, output_file: str, overwrite: bool = False, prefix: Optional[str] = None
    ):
        """@brief Constructs all needed attributes for the QrcGenerator object.

        @param output_file The output .qrc file.
        @param overwrite Overwrite the output file if it already exists (default is False).
        @param prefix The prefix to use in the resource file. Defaults to the directory name.
        """

        self.output_file = output_file
        self.overwrite = overwrite
        self.prefix = prefix if prefix is not None else "/"
        self.output_dir = os.path.dirname(os.path.abspath(output_file))
        self.current_prefix = None

    def generate_qrc(self, paths: List[str]):
        """@brief Generates the Qt resource file.

        @param paths The directory or files to include in the resource file.
        """

        if os.path.exists(self.output_file) and not self.overwrite:
            print(f"File {self.output_file} already exists. Appending to it.")
            mode = "a"
            # Remove the </RCC> tag at the end of the file
            with open(self.output_file, "r") as f:
                lines = f.readlines()
            if lines[-1].strip() == "</RCC>":
                with open(self.output_file, "w") as f:
                    f.writelines(lines[:-1])
        else:
            mode = "w"

        with open(self.output_file, mode) as f:
            if mode == "w":
                f.write("<RCC>\n")
            for path in paths:
                self._write_files(f, path)
            f.write("    </qresource>\n")
            f.write("</RCC>\n")

    def _write_files(self, f, path):
        """@brief Writes the files to the resource file.

        @param f The file object of the resource file.
        @param path The path to the directory or file.
        """

        new_prefix = self.prefix
        if new_prefix != self.current_prefix:
            if self.current_prefix is not None:
                f.write("    </qresource>\n")
            f.write('    <qresource prefix="{}">\n'.format(new_prefix))
            self.current_prefix = new_prefix
        if os.path.isdir(path):
            for root, dirs, files in os.walk(path):
                for filename in files:
                    self._write_file(f, os.path.join(root, filename))
        elif os.path.isfile(path):
            self._write_file(f, path)

    def _write_file(self, f, path):
        """@brief Writes a single file to the resource file.

        @param f The file object of the resource file.
        @param path The path to the file.
        """

        relative_path = os.path.relpath(path, self.output_dir)
        f.write("        <file>{}</file>\n".format(relative_path.replace("\\", "/")))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a Qt resource file.")
    parser.add_argument(
        "paths",
        nargs="+",
        help="The directory or files to include in the resource file.",
    )
    parser.add_argument("output_file", help="The output .qrc file.")
    parser.add_argument(
        "--overwrite",
        action="store_true",
        help="Overwrite the output file if it already exists.",
    )
    parser.add_argument(
        "--prefix",
        help="The prefix to use in the resource file. Defaults to the directory name.",
    )

    args = parser.parse_args()

    generator = QrcGenerator(args.output_file, args.overwrite, args.prefix)
    generator.generate_qrc(args.paths)
