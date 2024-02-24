# <img src="./src/app/app.png" alt="Projekt Icon" width="30px" height="auto" style="vertical-align: -12%;"> Meta-Daten-Editor
[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md)
[![es](https://img.shields.io/badge/lang-de-black.svg)](./README.de.md)

## Erste Schritte

Um das Projekt lokal einzurichten, folgen Sie diesen Schritten:


### Voraussetzungen

Was sie installieren müssen und wie sie es installieren.

### Installation

Schritt-für-Schritt-Anleitung, die Ihnen zeigt, wie Sie eine Entwicklungsumgebung einrichten.

## DEV erste Schritte

1. Installiere ``QT 6.6.2``: https://www.qt.io/blog/qt-6.6.2-released
2. Klonen Sie das Repository.
3. Navigieren Sie in das Projektverzeichnis.
4. Editiere die Pfade für QT in der [CMakeLists.txt](./CMakeLists.txt)
```sh
set(CMAKE_PREFIX_PATH "pfad/zu/QT/6.6.2/mingw_64")
set(CMAKE_CXX_COMPILER "pfad/zu/QT/Tools/mingw1120_64/bin/c++.exe")
set(CMAKE_C_COMPILER "pfad/zu/QT/Tools/mingw1120_64/bin/gcc.exe")
```
5. Wenn sie ``make`` besitzen: `make build` aus um das Projekt zu bauen.

   -> Alternativ: 
```sh
    # Configure
    cmake --no-warn-unused-cli \
            -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
            -DCMAKE_BUILD_TYPE:STRING=Release \
            -DCMAKE_C_COMPILER:FILEPATH=gcc \ #setze den Pfad zur gcc oder nutze die Umgebungsvariable
            -DCMAKE_CXX_COMPILER:FILEPATH=g++ \ #setze den Pfad zur g++ oder nutze die Umgebungsvariable
            -S$(SRC_DIR) \ #ersetze SRC_DIR mit dem Pfad zum Projekt
            -B$(BIN_DIR) \ #ersetze BIN_DIR  mit dem Pfad zum build Ordner
            -G "MinGW Makefiles"
    # Build
    cmake --build $(BIN_DIR) --config Release --target all -j 6 -- # Ersetze BIN_DIR mit dem gleichen build pfad von oben
```

## Doku erstellt mit

* [Doxygen Awesome CSS](https://jothepro.github.io/doxygen-awesome-css/) - Das CSS-Thema, das für die Dokumentation verwendet wurde
-> Erstellen mit: `make gendoc`

## Autoren

* [Muddyblack](https://github.com/Muddyblack)

## Lizenz

Dieses Projekt ist unter der MIT-Lizenz lizenziert - siehe die Datei [LICENSE](LICENSE) für Details