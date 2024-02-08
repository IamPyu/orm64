--Orm64 configuration
-- Startup (and exit) Message!
orm64_options.show_startup_message = true
orm64_options.startup_message = [[Welcome to orm64, edit your configuration in $HOME/.orm64.d/config.lua.
If that file does not exist create a configuration with `orm64.setup_config()`
Reload your configuration with `orm64.reload_config()`
And run `help` for a documentation.]]

orm64_options.exit_message = "Goodbye."

-- Prompt
orm64_options.prompt = "> " -- The prompt, its that text that is printed before your cursor.

-- Packages
orm64_options.packages = {} -- Manage packages by git repo, with the Orm64 Package Manager!
-- Simply insert a string with the git repo URI with a key name.
-- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
-- A more powerful way to manage packages may be added in the future, or you could make your own package manager!

-- You can also create some functions for yourself and use them in the Orm64 shell

MyFuncs = {}

function MyFuncs.ls(dir)
  os.execute("ls " .. dir)
end

function MyFuncs.touch(path)
  os.execute("touch " .. path)
end

function MyFuncs.mkdir(path)
  os.execute("mkdir " .. path)
end

-- Here is a cool way to set up your orm64_options

--local opts = {
--  startup_message = "Hello!",
--  prompt = "> ",
--  pacakges = {
--
--  }
--}
--
--for k, v in pairs(opts) do
--  orm64_options[k] = v
--end
