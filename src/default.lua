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
