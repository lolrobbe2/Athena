import os
import platform
import subprocess
import threading
import time
import zipfile

import urllib.request


# Define ANSI escape sequences for colors
class ConsoleColors:
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"
    CYAN = "\033[36m"
    RESET = "\033[0m"

premake_download_url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"


def install_premake_thread(installer_path):
    subprocess.run([installer_path, "/S"], check=True)


def run_premake_vs2022(args):
    subprocess.run(["vendor\\premake5",
                    "vs2022",
                    "--lib-type={0}".format(args.lib_type if args.lib_type else "SharedLib"),
                    "--api-type={0}".format(args.api_type if args.api_type else "CPP")
                    ], check=True)


def download_and_extract_premake():
    zip_file_path = "premake.zip"
    urllib.request.urlretrieve(premake_download_url, zip_file_path)

    with zipfile.ZipFile(zip_file_path, "r") as zip_ref:
        # Extract premake5.exe to the vendor folder
        zip_ref.extract("premake5.exe", "vendor")

    # Cleanup: Delete the downloaded ZIP file
    os.remove(zip_file_path)


def install_premake(force_install=False):
    # ask for permission to install premake
    if not force_install:
        permissionGranted = False
        while not permissionGranted:
            reply = (
                str(input("Would you like to install premake {0:s}? [Y/N]: "))
                .lower()
                .strip()[:1]
            )
            if reply == "n":
                return
            permissionGranted = reply == "y"
    else:
        print("force installing premake")

    # start downloading and extracting
    download_thread = threading.Thread(target=download_and_extract_premake)
    download_thread.start()

    dots_printed = 0
    while download_thread.is_alive():
        print("\033[A                             \033[A")
        print("installing premake:")
        for i in range(dots_printed):
            print(".", end="", flush=True)
        dots_printed += 1
        time.sleep(1)
        if dots_printed == 3:
            dots_printed = 0

    print("installed premake succesfully")


def is_premake_installed():
    if platform.system() == "Windows":
        return os.path.exists("vendor\\premake5.exe")
    else:
        return False


def premake(args):
    print("\n/*------------------------------------------*/")
    print("/*                   premake                */")
    print("/*------------------------------------------*/\n")
    print(ConsoleColors.YELLOW)
    print("lib-type: {0}\n".format(args.lib_type if args.lib_type else "default"))
    print("api-type: {0}\n".format(args.api_type if args.api_type else "default"))
    
    print(ConsoleColors.RESET)
    if not is_premake_installed():
        print("premake not installed")
        install_premake(args.force_premake)
    else:
        run_premake_vs2022(args)
        print("Premake5 executed successfully.")
