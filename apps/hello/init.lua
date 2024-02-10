return function (name)
  if name ~= nil then
    local fmt = string.format("Hello, %s!", name)
    print(fmt)
  else
    print("Hello, world!")
  end
end
