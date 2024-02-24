local user = require("user")

--Orm64 configuration
-- Startup (and exit) Message!
orm64_options.show_startup_message = true -- Change whether the startup message should show.

local currentUser = user.getUsername() -- Get the current user's username.
orm64_options.startup_message = string.format("Welcome to Orm64, %s!", currentUser) -- Configure the startup message here.
orm64_options.exit_message = string.format("Goodbye, %s!", currentUser) -- Configure the exit message here.

-- Prompt
orm64_options.prompt = string.format("%s@orm64> ", currentUser) -- The prompt, its that text that is printed before your cursor.

-- Packages
orm64_options.packages = {
  snowutil = "https://gitlab.com/IamPyu/snowutil"
} -- Manage packages by git repo, with the Orm64 Package Manager!
-- Simply insert a string with the git repo URI with a key name.
-- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
-- A more powerful way to manage packages may be added in the future, or you could make your own package manager!
