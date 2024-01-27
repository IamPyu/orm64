--Orm64 config
-- Startup Message!
orm64_options.startup_message = "welcome to orm64, edit your configuration in $HOME/.orm64.d/config.lua"

-- Prompt
orm64_options.prompt = "> " --[[
    The prompt! Its like the PS1 variable in GNU Bash.
    It is that text that is printed before your cursor in a normal terminal shell.
    Pretty
]]

-- Packages
orm64_options.packages = {} -- Manage packages by git repo, with the Orm64 Package Manager!
  -- Simply insert a string with the git repo URI with a key name.
  -- ex. {mylibrary = "https://git.example.com/gitLover69/mylibrary"}
  -- A more powerful way to manage packages may be added in the future, or you could make your own package manager!
