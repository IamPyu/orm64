# Welcome to Orm64!

THIS DOCUMENTATION IS OLD AND SHOULD NOT BE USED. (it still has some left over parts from the rust version for goodness sakes)
INSTEAD USE THE ORM64 MANPAGES OR THE WIKI.

It seems like you need help!

## Shell
You might be questioning why is this shell not working?
Thats because its not a shell for your system. Its a Lua REPL to control Orm64!

Anything that is not a reserved command Orm64 uses (like this help command) will be passed to Lua to evaluate and execute.

Here is a list of reserved commands: [
    exit - Exits Orm64
    help - Prints this manual
    srtupmsg - Prints your startup message
    api - Prints the API documentation
]

## Configuration
If you are running Orm64 for the first time, a directory would've been created at: $HOME/.orm64.d

There are a few files in there

First of all, you have the `software` directory. 
This directory contains all the software you have installed/created on your Orm64 system.
The project structure for software looks like: software/PROJECT_NAME/init.lua
Everything else in that directory is up to the software to decide.

You also have the glorious... `config.lua` file
Its where you configure Orm64 to its very core(not really).

We also have the `data` directory.
This stores data important to Orm64 and should not be used by software.
Software should use there own data directory.

We cant go on about directories without talking about the `home` directory.
This contains all the users, created by: *drumroll* You!
An operating system that has a filesystem cannot go without a user directory.

Now lets talk more about the `config.lua` and teach you how to configure Orm64!

## APIs

Orm64 has a few APIs to get things done. 

See the API documentation by using the `api` reserved command.
