import os
import sys
import argparse


def generate_qrc(paths, output_file, overwrite=False, prefix=None):
    output_dir = os.path.dirname(os.path.abspath(output_file))

    if prefix is None:
        prefix = "/"
    if os.path.exists(output_file) and not overwrite:
        print(f"File {output_file} already exists. Appending to it.")
        mode = "a"
        # Remove the </RCC> tag at the end of the file
        with open(output_file, "r") as f:
            lines = f.readlines()
        if lines[-1].strip() == "</RCC>":
            with open(output_file, "w") as f:
                f.writelines(lines[:-1])
    else:
        mode = "w"

    current_prefix = None

    with open(output_file, mode) as f:
        if mode == "w":
            f.write("<RCC>\n")
        for path in paths:
            if os.path.isdir(path):
                new_prefix = prefix
            else:
                new_prefix = prefix
            if new_prefix != current_prefix:
                if current_prefix is not None:
                    f.write("    </qresource>\n")
                f.write('    <qresource prefix="{}">\n'.format(new_prefix))
                current_prefix = new_prefix
            if os.path.isdir(path):

                for root, dirs, files in os.walk(path):
                    for filename in files:
                        relative_path = os.path.relpath(
                            os.path.join(root, filename), output_dir
                        )
                        f.write(
                            "        <file>{}</file>\n".format(
                                relative_path.replace("\\", "/")
                            )
                        )
            elif os.path.isfile(path):
                relative_path = os.path.relpath(path, output_dir)
                f.write(
                    "        <file>{}</file>\n".format(relative_path.replace("\\", "/"))
                )

        f.write("    </qresource>\n")
        f.write("</RCC>\n")


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

    generate_qrc(args.paths, args.output_file, args.overwrite, args.prefix)
