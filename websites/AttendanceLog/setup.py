from venv import create
from subprocess import call, run
from os import path, makedirs
import signal

if not path.exists("./venv"):
    print("Creating Python virtual environment...")
    create("./venv", with_pip=True)


print("Installing pip packages from `requirement.txt` file...")
run(["./venv/Scripts/pip.exe", 'install', '-q', '--disable-pip-version-check', '-r', './requirements.txt'])

print("Freezing pip packages in `freeze.txt` file...")
with open('./freeze.txt', 'w') as file:
    call(["./venv/Scripts/pip.exe", 'freeze'], stdout=file)

logs_dir="logs"
if not path.exists(logs_dir):
    makedirs(logs_dir)

run(["./venv/Scripts/python.exe", "./web.py", "--extra-files", "data/"])