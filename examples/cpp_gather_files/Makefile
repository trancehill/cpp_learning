CC = g++
CC_FLAGS = -O3 -Wall -std=c++17
LD_FLAGS =
NAME = myprogram
SOURCE_DIR = ./src
SOURCE_FILES = $(shell find $(SOURCE_DIR) -type f -iregex '.*\.\(c\|i\|ii\|cc\|cp\|cxx\|cpp\|CPP\|c++\|C\|s\|S\|sx\)' )
OUTPUT_DIR = ./output
INSTALL_DIR = /usr/local/bin

all: $(OUTPUT_DIR) $(SOURCE_FILES) 
	$(CC) $(CC_FLAGS) $(SOURCE_FILES) -o "$(OUTPUT_DIR)/$(NAME)" $(LD_FLAGS)

.PHONY: install
install: all
	cp $(OUTPUT_DIR)/$(NAME) $(INSTALL_DIR)/$(NAME)

.PHONY: clean
clean: 
	rm -rf $(OUTPUT_DIR)
	
.PHONY: uninstall
uninstall:
	rm -rf $(INSTALL_DIR)/$(NAME)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)
