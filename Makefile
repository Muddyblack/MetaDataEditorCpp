# Compiler executables
CC := gcc
CXX := g++

# Directories
SRC_DIR := $(CURDIR)
BIN_DIR := $(SRC_DIR)/build

# Build targets and commands
start:
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

gendoc:
	@cd documentation && python update_readme.py
	@cd documentation && doxygen Doxyfile
	@make opendoc

ressgen:
	@cd resources && python run_ress_gen.py

opendoc:
ifeq ($(OS),Windows_NT)
	@cd documentation && ".\doc_website\html\index.html"
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		@cd documentation && xdg-open ./doc_website/html/index.html
	endif
	ifeq ($(UNAME_S),Darwin)
		@cd documentation && open ./doc_website/html/index.html
	endif
endif