return function ()

  local graphics = require("graphics")
  local window = graphics.new(800, 600, "Coloring")
  window:init()

  local size = DRAW_SIZE or 20
  local color = DRAW_COLOR or {0, 0, 0}
  local colors = {

  }

  print("Set DRAW_SIZE variable to a number to change the drawing size!")
  print("Set DRAW_COLOR variable to a RGB table to change the drawing color!")

  while not window:shouldClose() do
    if window:isMouseButtonDown(graphics_mousebutton.LEFT) then
      local x, y = window:getMousePos()
      table.insert(colors, {x, y})
    end

    window:draw(function()
      window:setDrawColor(255, 255, 255, 255)
      window:clearBackground()

      window:setDrawColor(color[1], color[2], color[3], 255)

      for _, v in pairs(colors) do
        window:drawCircle(v[1], v[2], size)
      end
    end)
  end

  window:close()
end
