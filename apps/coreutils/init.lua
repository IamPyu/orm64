local user = require("user")
local function ls(p)
   local path = user.getPath() .. "/"
   os.execute("ls -a " .. path .. (p ~= nil and p or ""))
end

local function touch(p)
   local path = user.getPath() .. "/"
   os.execute("touch " .. path .. p)
end

local function mkdir(p)
   local path = user.getPath() .. "/"
   os.execute("mkdir " .. path .. p)
end

return {
  ls = ls,
  touch = touch,
  mkdir = mkdir
}
