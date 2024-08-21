import argparse
import os
import subprocess
import platform
import threading
import time
import zipfile
from scripts.setupPremake import premake
from scripts.setupPython import PythonConfiguration as PythonRequirements

# Function to map 'Static' to 'StaticLib' and 'Shared' to 'SharedLib'

def api_type_mapping(value):
    mapping = {
        "C-API":"C",
        "CPP-API":"CPP",
        "C":"C",
        "CPP":"CPP",
        "COMBINED":"COMBINED"
    }
    if value not in mapping:
        raise argparse.ArgumentTypeError(f"Invalid choice: {value} (choose from 'CPP', 'CPP-API', 'C', 'C-API,COMBINED')")
    return mapping[value]

def lib_type_mapping(value):
    mapping = {
        'Static': 'StaticLib',
        'Shared': 'SharedLib',
        'StaticLib': 'StaticLib',
        'SharedLib': 'SharedLib'
    }
    if value not in mapping:
        raise argparse.ArgumentTypeError(f"Invalid choice: {value} (choose from 'SharedLib', 'Shared', 'StaticLib', 'Static')")
    return mapping[value]

def main():
    # parse options
    parser = argparse.ArgumentParser(description="Install Premake and run premake.")
    #these are used for pipeline building
    parser.add_argument(
        "--force-premake",
        action="store_true",
        help="Install premake without asking for permission.",
    )

    parser.add_argument(
        "--force-python",
        action="store_true",
        help="Install pyhton packages without asking for permission.",
    )
    parser.add_argument(
        "--enable-WSL",
        action="store_true",
        help="enables windows subsystem for linux building of Athena"
    )
    parser.add_argument(
        "--api-type",
        type=api_type_mapping,
        choices=['C-API','C','CPP-API','CPP','COMBINED'],
        help="Choose a api type."   
        
    )
    parser.add_argument(
        "--lib-type",
        type=lib_type_mapping,
        choices=['SharedLib','Shared','StaticLib','Static'],
        help="Choose a library type."   
        
    )
    args = parser.parse_args()

    PythonRequirements.Validate(args.force_python)
    premake(args)
    input("Press Enter to continue...")

if __name__ == "__main__":
    main()
