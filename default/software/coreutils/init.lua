if user == nil then
  print("Orm64 coreutils Application requires bloat mode.")
  return 1
end

local user = require("user")

local function ls(f)
   local path = user.getPath() .. "/"
   os.execute("ls -a " .. path .. (f ~= nil and f or ""))
end

local function touch(p)
   local path = user.getPath() .. "/"
   os.execute("touch " .. path .. p)
end

local function mkdir(p)
   local path = user.getPath() .. "/"
   os.execute("mkdir " .. path .. p)
end

local function cat(f)
  local path = string.format("%s/%s", user.getPath(), f)
  local file = io.open(path, "r")
  if file ~= nil then
    print(file:read("a"))
  else
    print(string.format("Failed to open file: %s", f))
  end
end

return {
  ls = ls,
  touch = touch,
  mkdir = mkdir,
  cat = cat
}
