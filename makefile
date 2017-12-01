### Cpp Arguments
CC=g++
CFLAGS=-std=c++11

### Program Arguments
NAME=khash

### Compiler Arguments
SRC=src

all: main

main: $(SRC)/main.cc $(SRC)/strutils.hh $(SRC)/khash.hh
	$(CC) $(CFLAGS) $(SRC)/main.cc -o $(NAME)
