# Compiler executables
CC := gcc
CXX := g++

# Directories
SRC_DIR := $(CURDIR)
BIN_DIR := $(SRC_DIR)/build
DOXYGEN_INDEX_FILE := $(SRC_DIR)/documentation/DOXYGEN/html/index.html

# Build targets and commands
build:
	@cmake --no-warn-unused-cli \
	       -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
	       -DCMAKE_BUILD_TYPE:STRING=Release \
	       -DCMAKE_C_COMPILER:FILEPATH=$(CC) \
	       -DCMAKE_CXX_COMPILER:FILEPATH=$(CXX) \
	       -S$(SRC_DIR) \
	       -B$(BIN_DIR) \
	       -G "MinGW Makefiles"

	@cmake --build $(BIN_DIR) --config Release --target all -j 6 --

	@$(BIN_DIR)/MetaDataEditor

doc:
	@cd documentation && python update_readme.py
	@cd documentation && doxygen Doxyfile
	@make opendoc

ressgen:
	@cd resources && python run_ress_gen.py

opendoc:
ifeq ($(OS),Windows_NT)
	@cd documentation && start "" "$(DOXYGEN_INDEX_FILE)"
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		@xdg-open $(DOXYGEN_INDEX_FILE)
	endif
	ifeq ($(UNAME_S),Darwin)
		@open $(DOXYGEN_INDEX_FILE)
	endif
endif