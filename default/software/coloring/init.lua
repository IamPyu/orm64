return function ()
  local graphics = require("graphics")
  local window = graphics.new(800, 600, "Coloring")
  window:init()

  while not window:shouldClose() do
    window:draw(function()
      window:setDrawColor(255, 255, 255, 255)
      window:clearBackground()
      
      if window:isMouseButtonPressed(graphics_mousebutton.LEFT) then
        print(32)
      end
    end)
  end

  window:close()
end