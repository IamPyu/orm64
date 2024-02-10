local function ls(p)
  local user = require("user")
  local path = user.getPath() .. "/"
  os.execute("ls -a " .. path .. (p ~= nil and p or ""))
end

local function touch(p)
  local user = require("user")
  local path = user.getPath() .. "/"
  os.execute("touch " .. path .. p)
end

return {
  ls = ls,
  touch = touch
}
