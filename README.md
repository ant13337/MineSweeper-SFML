# MineSweeper (SFML, C++)

This is a Minesweeper game written in C++ with SFML.

## What Is In This Repository

- Source code and Visual Studio solution: `CodePC`
- Project files configured for SFML 2.5.0

This GitHub repo currently tracks source and project files. Build output (`Bin`), object files (`Obj`), and local SFML folders are not committed.

Required runtime assets are included:

- `Bin/Images` (textures)
- `Bin/times.txt` (best-time log)

## Prerequisites

- Visual Studio 2022 with MSVC toolset (v143)
- SFML 2.5.0 for your target architecture (x64 and/or x86)

## Setup

The `.vcxproj` is configured to look for SFML in these paths:

- `External/x64/SFML-2.5.0`
- `External/x86/SFML-2.5.0`

The code loads textures from `../Images/...` and writes times to `../times.txt` relative to the generated `.exe` in `Bin/x64` or `Bin/x86`.

## Build And Run

1. Open `CodePC/DV1627.sln` in Visual Studio.
2. Select configuration (`Debug` or `Release`) and platform (`x64` or `Win32`).
3. Build the `Template` project.
4. Run the produced executable in `Bin/x64` or `Bin/x86`.

Typical executable names:

- Debug: `TemplateD.exe`
- Release: `Template.exe`

## Dependencies

This project uses SFML 2.5.0.

- SFML license: zlib/png-style license
- Additional third-party notes: `THIRD_PARTY_LICENSES.md`

## License

This project is licensed under the MIT License.
See `LICENSE` for details.
