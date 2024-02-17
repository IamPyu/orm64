# orm64

A simple, lua-based, fantasy operating system.

It's kinda like those fantasy game consoles, except its meant to be an enitre OS.

## Why?

Because I had enough of making FizzBuzz projects!

## Dependencies

In order to use this program you will need the dependencies listed below:

- Unix based system, (MacOS and Linux tested, unsure about BSDs)
- LuaJIT
- Raylib
- ncurses
- pkg-config
- libedit
- git

## Building

Simply use `build.sh`

## Features

- [X] Lua REPL
- [X] Application, and Libraries
- [X] Package manager (To install apps and libraries)
- [ ] An API with a bunch of modules to create lots of things
    - [X] Graphics and Multimedia layer
    - [ ] Terminal Manipulation library
    - [ ] Networking and HTTP library
- [ ] Plugin system
- [X] User system

## History

I first wrote this in [Rust](https://rust-lang.org).

But of course I had issues with the borrow checker and the [mlua](https://github.com/mlua-rs/mlua) API

So I decided to rewrite Orm64 in C, since C lets you do just about anything in any way you want.

I found pointers easy and I ended up really liking C. I guess from now on I will write most of my projects in C!
