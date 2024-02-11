# NAME

orm64 - Fantasy operating system

# DESCRIPTION

Orm64 is a fantasy operating system, or what I call a "Utility system"

It features:

- A package manager
- Multiple APIs to create applications
- A Lua REPL
- Extensibility with Lua
- A user system
- And more!

# TUTORIAL

To get started, we have to run Orm64 which is really simple!
Just enter 'orm64' into a shell like you would with any other command.

You will be met with a login screen, for now we are just going to use the 'guest' user.

If Orm64 is installed properly, you should be met with a prompt that looks like this: '> '.

Now let's create your own user!

Run the lua function 'orm64.createUser("NAME", "PASSWORD")', replace NAME and PASSWORD with your own name and password.

Now exit Orm64 by using the 'exit' command.


Restart Orm64 and enter your chosen username and password.

Hooray! You have logged into your user.

Lets use a user function.

Enter 'coreutils = require("coreutils")' into the prompt.

If everything worked you can now use the coreutils package, otherwise you may need to reinstall Orm64.


