return function ()
  local graphics = require("graphics")
  local window = graphics.new(800, 600, "Coloring")
  window:init()

  while not window:shouldClose() do
    window:draw(function()
      window:clearBackground(255, 255, 255, 255)
    end)
  end

  window:close()
end