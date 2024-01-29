--Orm64 config
-- Startup Message!
orm64_options.startup_message = [[Welcome to orm64, edit your configuration in $HOME/.orm64.d/config.lua.
If that file does not exist create a configuration with `orm64.setup_config()`
Reload your configuration with `orm64.reload_config()`
And run `help` for a documentation.]]

-- Prompt
orm64_options.prompt = "> " -- The prompt, its that text that is printed before your cursor.

-- Packages
orm64_options.packages = {} -- Manage packages by git repo, with the Orm64 Package Manager!
-- Simply insert a string with the git repo URI with a key name.
-- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
-- A more powerful way to manage packages may be added in the future, or you could make your own package manager!

-- You can also create some functions for yourself and use them in the Orm64 shell

orm64_examples = {}

function orm64_examples.greet(name)
	local str = string.format("Hello, %s!\n", name)
	io.stdout:write(str)
end

function orm64_examples.game()
	local graphics = require("graphics")
	local window = graphics.new(800, 600, "My Window")

	window:init()

	while not window:shouldClose() do
		window:draw(function()
			window:setDrawColor(135, 206, 235, 255)
			window:clearBackground()
		end)
	end

	window:close()
end
