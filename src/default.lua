--Orm64 configuration
-- Startup (and exit) Message!
orm64_options.show_startup_message = true
orm64_options.startup_message = "Welcome to Orm64!"

orm64_options.exit_message = "Goodbye."

-- Prompt
orm64_options.prompt = "> " -- The prompt, its that text that is printed before your cursor.

-- Packages
orm64_options.packages = {} -- Manage packages by git repo, with the Orm64 Package Manager!
-- Simply insert a string with the git repo URI with a key name.
-- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
-- A more powerful way to manage packages may be added in the future, or you could make your own package manager!
