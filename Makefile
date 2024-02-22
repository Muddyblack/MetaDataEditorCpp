start:
	@cmake -E make_directory build && cd build && cmake .. && cmake --build . --config Release && MetaDataEditor

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