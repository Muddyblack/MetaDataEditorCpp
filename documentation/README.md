# <img src="../../../src/app/app.png" alt="Project Icon" width="30px" height="auto" style="vertical-align: -12%;"> Meta-Data Editor

<a href="../../../README.md"><img src="https://img.shields.io/badge/lang-en-red.svg" alt="English"></a>
<a href="../../../README.de.md"><img src="https://img.shields.io/badge/lang-de-black.svg" alt="German"></a>

## Getting Started

To set up the project locally, follow these steps:

### Prerequisites

What you need to install and how to install it.

### Installation

Step-by-step guide showing you how to set up a development environment.

## For DEV

### Recommendation
* Use [CLion](https://www.jetbrains.com/de-de/clion/)

#### For VSCODE DEVS
1. [Cmake-twxs](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
2. [C/C++_Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
3. [CMake_Tools_Fork](https://marketplace.visualstudio.com/items?itemName=maxmitti.cmake-tools-fork)
4. [Makefile_Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)

1. Install ``QT 6.6.2``: https://www.qt.io/blog/qt-6.6.2-released
2. Clone the repository.
3. Navigate to the project directory.
4. Edit the paths for QT in the [CMakeLists.txt](../../../CMakeLists.txt)
```sh
set(CMAKE_PREFIX_PATH "path/to/QT/6.6.2/mingw_64")
set(CMAKE_CXX_COMPILER "path/to/QT/Tools/mingw1120_64/bin/c++.exe")
set(CMAKE_C_COMPILER "path/to/QT/Tools/mingw1120_64/bin/gcc.exe")
```
5. If you have ``make``: run ``make`` or ``make build`` to build the project.

-> Alternatively: 
```sh
    # Configure
    cmake --no-warn-unused-cli \
            -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DCMAKE_C_COMPILER:FILEPATH=gcc \ #set path to gcc or use env variable
            -DCMAKE_CXX_COMPILER:FILEPATH=g++ \ #set path to g++ or use env variable
            -S$(SRC_DIR) \ #replace SRC_DIR with path of project
            -B$(BIN_DIR) \ # replace BIN_DIR  path to build folder
            -G "MinGW Makefiles"
    # Build
    cmake --build $(BIN_DIR) --config Release --target all -j 6 -- # Replace BIN_DIR like you did above
```

## Documentation build with

* [Doxygen Awesome CSS](https://jothepro.github.io/doxygen-awesome-css/) - The CSS theme used for 
* Open it using: ``make opendoc``

### Required
* ``Python`` for updating the URL's of the readme files 

### Optional 
* ``Graphviz`` for graphs in documentation 

### Generating
* Generate with: ``make doc`` Requires python for updating readme paths


## Authors

* [Muddyblack](https://github.com/Muddyblack)

## License
This project is licensed under the MIT License - see the [LICENSE](../../../LICENSE) file for details