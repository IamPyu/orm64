local function hello(name)
   if name ~= nil then
      if type(name) == "string" then
	 local fmt = string.format("Hello, %s!", name)
	 print(fmt)
      elseif type(name) == "table" then
	 for _, v in pairs(name) do
	    hello(v)
	 end
      end
   else
      print("Hello, world!")
   end
end

return hello
