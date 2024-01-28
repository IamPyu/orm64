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

The graphics is based on Raylib, originially I was gonna have based on SDL2 but I dont like SDL2.

### Basic Drawing

Lets make a simple window.

```lua
local graphics = require("graphics")
local window = graphics.new(800, 600, "My Window")

window:init()

while not window:shouldClose() do
    window:draw(function()
    
    end)
end

window:close()
```

That is the code for a basic window.

Save your code in ~/.orm64.d/software/mywindow/init.lua

And in Orm64 run `require("mywindow")`

You should see an empty window appear.

Lets analyze the code! If you are familiar with Raylib things *might* make sense.

First, we require the graphics api (This is optional, as graphics is still a global).

Then we create a "graphics" object called `window`, the first parameter for `graphics.new` is the width of the window, second is height, and third is the title.

`window:init()` calls the raylib function `InitWindow` with the parameters we used for `graphics.new`.

If we remove `window:init()` we should get a segmentation fault.

Then, we have a loop thats loops until the window wants to close.

The `window:draw()` function takes a function as an input and calls it between the raylib functions `BeginDrawing` and `EndDrawing`

`window:close()` just calls the raylib function `CloseWindow`.

Now lets actually start drawing shapes to the screen!

I all of a sudden have the feeling to show you the definition of the `graphics` object.

```c
typedef struct {
    const char *title;
    int width;
    int height;

    lua_CFunction draw;
    Color drawColor;    
} Graphics;
```

So you can see we have the title, width and height variables.

Then we have the draw function.

But there is one last one which is the draw color.

You can change the draw color using `window:setDrawColor(red, green, blue, alpha)` and change the red, green, blue and alpha parameters to the RGBA codes you want.

Here is our previous example, but with a sky blue background

```lua
local graphics = require("graphics")
local window = graphics.new(800, 600, "My Window")

window:init()

while not window:shouldClose() do
    window:draw(function()
        window:setDrawColor(135, 206, 235, 255)
        window:clearBackgroud()
    end)
end

window:close()
```