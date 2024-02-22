# <img src="./src/app/app.png" alt="Project Icon" width="30px" height="auto" style="vertical-align: -12%;"> Meta-Data Editor

<a href="./README.md"><img src="https://img.shields.io/badge/lang-en-red.svg" alt="English"></a>
<a href="./README.de.md"><img src="https://img.shields.io/badge/lang-de-black.svg" alt="German"></a>

## Getting Started

To set up the project locally, follow these steps:

### Prerequisites

What you need to install and how to install it.

### Installation

Step-by-step guide showing you how to set up a development environment.

## DEV Getting Started

1. Install ``QT 6.6.2``: https://www.qt.io/blog/qt-6.6.2-released
2. Clone the repository.
3. Navigate to the project directory.
4. Edit the paths for QT in the [CMakeLists.txt](./CMakeLists.txt)
```sh
set(CMAKE_PREFIX_PATH "path/to/QT/6.6.2/mingw_64")
set(CMAKE_CXX_COMPILER "path/to/QT/Tools/mingw1120_64/bin/c++.exe")
set(CMAKE_C_COMPILER "path/to/QT/Tools/mingw1120_64/bin/gcc.exe")
```
5. If you have ``make``: run ``make start`` to build the project.

-> Alternatively: ``mkdir build && cd build && cmake .. && cmake .``

## Build With

* [Doxygen Awesome CSS](https://jothepro.github.io/doxygen-awesome-css/) - The CSS theme used for documentation 
    * Generate with: ``make gendoc`` Requires python for updating readme paths

## Authors

* [Muddyblack](https://github.com/Muddyblack)

## License
This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details