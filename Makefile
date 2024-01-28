CC:=gcc # c compiler
CLFAGS+=-Wall -std=gnu18 # main flags
CLFAGS+=-lluajit -lraylib -lSDL2 -lncurses # libraries
CLFAGS+=$(shell pkg-config --libs --cflags libedit) # libraries found by pkg-config

SRC:=$(shell find . -name "*.c")
OUT:=bin/orm64

.PHONY: all

all: build

build:
	@mkdir -p bin
	@sh setup.sh
	@$(CC) $(CLFAGS) $(SRC) -o $(OUT)

run: build
	@$(OUT)

clean:
	@rm -rf bin
