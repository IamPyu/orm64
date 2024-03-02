return function ()
   local multimedia = require("multimedia")
   local graphics = require("graphics")
   local window = graphics.new(1200, 800, "Gamepads")

   local X = 400
   local Y = 300
   local Size = 45
   local Speed = 5
   
   math.randomseed(os.time())
   local Color = {
	  math.random(0, 255),
	  math.random(0, 255),
	  math.random(0, 255),
	  math.random(0, 255)
   }

   multimedia.init()
   window:init()
   window:setTargetFPS(60)
   
   while not window:shouldClose() do
	  if window:isGamepadButtonDown(0, graphics_gamepadbutton.RIGHT) then
		 X = X + Speed
	  end

	  if window:isGamepadButtonDown(0, graphics_gamepadbutton.LEFT) then
		 X = X - Speed
	  end

	  if window:isGamepadButtonDown(0, graphics_gamepadbutton.DOWN) then
		 Y = Y + Speed
	  end

	  if window:isGamepadButtonDown(0, graphics_gamepadbutton.UP) then
		 Y = Y - Speed
	  end

	  if window:isGamepadButtonPressed(0, graphics_gamepadbutton.X) then
		 window:toggleFullscreen()
	  end
	  
	  if window:isGamepadButtonPressed(0, graphics_gamepadbutton.A) then
		 X = 400
		 Y = 300
	  end
	  
	  if window:isGamepadButtonPressed(0, graphics_gamepadbutton.B) then
		 local path = orm64.getSoftwarePath("sounds")
		 if path ~= nil then
			multimedia.playSound(path.."/sound.mp3")
		 end
	  end
	  
	  window:draw(function()
			window:setDrawColor(255, 255, 255, 255)
			window:clearBackground()

			-- Player
			window:setDrawColor(Color[1], Color[2], Color[3], Color[4])
			window:drawCircle(X, Y, Size)

			-- House
			window:setDrawColor(40, 0, 0, 255)
			window:drawRect(0, 400, 180, 800-400)
	  end)
   end

   window:close()
   multimedia.close()
end
