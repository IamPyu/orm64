return function()
   local path = orm64.getSoftwarePath("sounds") -- Looks for "sounds" program, do not rename

   if path ~= nil then
	  local graphics = require("graphics")
	  local window = graphics.new(800, 600, "Sounds")
	  window:init()

	  
	  while not window:shouldClose() do
		 if window:isKeyPressed(graphics_keys.SPACE) then
			print(path)
			window:playSound(path.."/sound.mp3")
		 end
		 
		 window:draw(function()
			   window:setDrawColor(255, 255, 255, 255)
			   window:clearBackground()
			   
			   window:setDrawColor(0, 0, 0, 255)
			   window:drawText("Press SPACE to play a sound!", 0, 0, 28)
		 end)
	  end

	  window:close()
  end
end
