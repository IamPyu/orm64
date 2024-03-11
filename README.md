# orm64

A simple, lua-based, fantasy operating system.

It's kinda like those fantasy game consoles, except its meant to be an enitre OS.

## Update March 9th 2024

The term "fantasy console" or "fantasy operating system" for Orm64 does not make sense.

Instead Orm64 will be labelled as "an API layer for creating Software with Lua.".

Which makes features like "Users" useless and bloated, *which is good (Just kidding!)*.

## License and Contributing

Orm64 is licensed under the MIT License. You are free to copy, modify, distribute, and sublicense this project.

Media created by me in this project are licensed under also under the MIT license because I don't want to use another license.


## Roadmap

- [X] Lua REPL
- [X] Application, and Libraries
- [X] C/C++ Library for interacting with Orm64

### APIs

- [X] Graphics and Multimedia API
- [X] User system and user interaction API (Bloated build only)
- [ ] Networking and HTTP API 

#### Users

- [ ] File system

### Configuration

- [X] Configuration via Lua
- [X] Plugins via C
- [ ] Lots of configuratin options
- [ ] More features for Plugins

## History

I first wrote this in [Rust](https://rust-lang.org).

But of course I had issues with the borrow checker and the [mlua](https://github.com/mlua-rs/mlua) API

So I decided to rewrite Orm64 in C, since C lets you do just about anything in any way you want.

I found pointers and memory allocation (Thanks to my experience in Rust) easy and I ended up really liking C. 
I guess from now on I will write most of my projects in C!

I rewrote this in C++ a month after the C rewrite for some nice features like the *new* and *delete* keywords and lambdas.

I later discovered that C++ is an unholy abomination of a language and rewrote it in C again.

## Other stuff

This project **probably** has a bunch of crappy code.
But don't blame me it's my first big C/C++ project in 2 years.
