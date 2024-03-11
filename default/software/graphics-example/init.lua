return function()
  local FONT_SIZE = 22

  local graphics = require("graphics")
  local window = graphics.new(440, 220, "GUI")
  window:init()

  while not window:shouldClose() do
    window:draw(function ()
      window:setDrawColor(255, 255, 255, 255)
      window:clearBackground()

      window:setDrawColor(0, 0, 0, 255)
      if user ~= nil then
        window:drawText(user.getUsername(), 0, 0, FONT_SIZE)
      else
        window:drawText("User functionality is disabled.", 0, 0, FONT_SIZE)
      end

      window:setDrawColor(0, 180, 180, 255)
      window:drawCircle(330, 80, 70)
    end)
  end

  window:close()
end
