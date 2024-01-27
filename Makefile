CC:=gcc # c compiler
CLFAGS+=-Wall -std=gnu18 # main flags
CLFAGS+=-lluajit -lraylib -lncurses # libraries
CLFAGS+=$(shell pkg-config --libs --cflags libedit) # libraries found by pkg-config

SRC:=$(shell find . -name "*.c")
OUT:=bin/orm64

.PHONY: all

all: build

build: setup
	@sh setup.sh
	@$(CC) $(CLFAGS) $(SRC) -o $(OUT)

run: build
	@$(OUT)

setup:
	@mkdir -p bin

install: build
	@echo "Run the `install` target with sudo."
	@echo "TODO"

clean:
	@rm -rf bin