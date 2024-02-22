import os
import subprocess

script_dir = os.path.dirname(os.path.realpath(__file__))
print(script_dir)
script_path = os.path.join(script_dir, "resources_gen.py")
print(script_path)

os.chdir(script_dir)


def run_generate_qrc(paths, output_file, overwrite=False, prefix=None):
    if isinstance(paths, str):
        paths = [paths]

    command = ["python", script_path] + paths + [output_file]
    if overwrite:
        command.append("--overwrite")
    if prefix is not None:
        command.extend(["--prefix", prefix])
    subprocess.run(command)


RESOURCEFILE = f"{script_dir}/resources.qrc"


run_generate_qrc(
    paths=[f"{script_dir}/styles"],
    output_file=RESOURCEFILE,
    overwrite=True,
)

run_generate_qrc(
    paths=[f"{script_dir}/resources", f"{script_dir}/app.ico"],
    output_file=RESOURCEFILE,
    overwrite=False,
)
