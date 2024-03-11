--Orm64 configuration
-- Startup (and exit) Message!
orm64_options.show_messages = true -- Change whether messages should show.

if user ~= nil then -- Check if user module exists (Since Orm64 has a build option to disable users.)
  -- Startup message, exit message, etc.
  local currentUser = user.getUsername() -- Get the current user's username.
  orm64_options.startup_message = string.format("Welcome to Orm64, %s!", currentUser) -- Configure the startup message here.
  orm64_options.exit_message = string.format("Goodbye, %s!", currentUser) -- Configure the exit message here.

  -- Prompt
  orm64_options.prompt = string.format("%s> ", currentUser) -- The prompt, its that text that is printed before your cursor.
else -- Otherwise, we will have defaults without user functionality.
  -- Startup message, exit message, etc.
  orm64_options.startup_message = "Welcome to Orm64!"
  orm64_options.exit_message = "Goodbye!"
  -- Prompt
  orm64_options.prompt = "> "
end


-- Packages
orm64_options.packages = {
  snowutil = "https://gitlab.com/IamPyu/snowutil"
} -- Manage packages by git repo, with the Orm64 Package Manager!
-- Simply insert a string with the git repo URI with a key name.
-- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
-- A more powerful way to manage packages may be added in the future, or you could make your own package manager!

