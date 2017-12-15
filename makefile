#!/bin/bash
### Cpp Arguments
CC=g++
CFLAGS=-std=c++11

### Program Arguments
NAME=khash
NAME_BUILD=khash-exec

### Compiler Arguments
SRC=src

all: main

main: $(SRC)/main.cc $(SRC)/strutils.hh $(SRC)/khash.hh
	$(CC) $(CFLAGS) $(SRC)/main.cc -o $(NAME)

build: all move

move:
	@echo "Writting script"
	@echo 'if [ "$$1" == "e" ]' > $(NAME_BUILD)
	@echo 'then' >> $(NAME_BUILD)
	@echo '"$(CURDIR)/$(NAME)" "e" "$${PWD}/$$2" "$${PWD}/$$3"' >> $(NAME_BUILD)
	@echo 'elif [ "$$1" == "r" ]' >> $(NAME_BUILD)
	@echo '"$(CURDIR)/$(NAME)" "r" "$${PWD}/$$2" "$$3"' >> $(NAME_BUILD)
	@echo 'fi' >> $(NAME_BUILD)
	chmod +x $(NAME)
	chmod +x $(NAME_BUILD)
	cp $(NAME_BUILD) /usr/bin