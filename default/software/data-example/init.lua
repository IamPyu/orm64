---@param data string
return function(data)
  local dir = orm64.getSoftwarePath("data-example")
  print("Software path is: " .. dir)
  local file = io.open(dir.."/data", "r")

  if file ~= nil then
    print("Current data is: " .. file:read("a"))
    file:close()

    local file = io.open(dir .. "/data", "w")
    if file ~= nil then
      print("New data will be: " .. data)
      file:write(data)
      file:flush()

      file:close()
    else
      print("Failed to open file for writing")
    end
  else
    print("Failed to open file for writing")
  end
end