# The API

* You are not limited to this API as users can create their own libraries.

## Most used functions and variables: The orm64 table

The first function you will learn from this documententation is the *amazing* the *indestructible* the amazing: `orm64.get_software_path`.

This function returns the path of a specified software.

If the path does NOT exist, it returns nil.

Be sure to use nil-checking before using the result from the function so no bugs appear in your program.

There is also `orm64.setup_config`.

If you do not have a configuration setup, run the function for a brand new configuration!

Now we have `orm64.reload_config`.

It is pretty self explanatory, if you change your configuration while Orm64 is running you do not have to exit Orm64.
Instead you can run the function and your configuration is "magically" reloaded.

It's not actually magical, as it just resources `~/.orm64.d/config.lua`

Git time. You can use `orm64.install_packages` to install your configured packages in your configuration.

## The Graphics and Multimedia APIs

The whole reason I made Orm64 was to make a simple game console that runs on your computer.

So of course we need graphics and multimedia.

Unless you want to make graphics from scratch using the CPU or with OpenGL bindings, you should use this API for graphics.
