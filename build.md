# Athena Build Instructions

To build Athena, you can run the `BUILD.bat` (for Windows) or `BUILD.sh` (for Unix-based systems). These scripts simply execute the `build.py` Python script for convenience.

For additional options, you can run:

```bash
python build.py --help
```

## Build Options

Here are the options you can use with the `build.py` script:

- **`--force-premake`**  
  *Install Premake without asking for permission.*  
  Use this option if you want to force the installation of Premake, bypassing any prompts.

- **`--force-python`**  
  *Install Python packages without asking for permission.*  
  This option forces the installation of required Python packages without user confirmation.

- **`--enable-WSL`**  
  *Enable Windows Subsystem for Linux (WSL) for building Athena.*  
  Use this if you prefer to build Athena using WSL on a Windows system.

- **`--api-type`**  
  *Choose an API type.*  
  This option allows you to specify the type of API to be used. The choices are:
  - `C-API` or `C`
  - `CPP-API` or `CPP`
  - `COMBINED`
  - `NONE` or `none` (Default)

- **`--lib-type`**  
  *Choose a library type.*  
  Specify the type of library to be built. The choices are:
  - `SharedLib` or `Shared`
  - `StaticLib` or `Static` (Default)

These options provide flexibility in configuring the build process according to your specific needs.
