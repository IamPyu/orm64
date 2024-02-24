return function()
   local user = require("user")
   local graphics = require("graphics")
   local window = graphics.new(440, 220, "GUI")
   window:init()
   
   while not window:shouldClose() do
      window:draw(function ()
            window:setDrawColor(255, 255, 255, 255)
            window:clearBackground()
	    
            window:setDrawColor(0, 0, 0, 255)
            window:drawText(user.getUsername(), 0, 0, 22)
	    
            window:setDrawColor(0, 180, 180, 255) 
            window:drawCircle(330, 80, 70)
      end)
   end
   
   window:close()
end
