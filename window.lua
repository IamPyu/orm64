local graphics = require("graphics")
local window = graphics.new(800, 600, "My Window")

window:init()

while not window:shouldClose() do
    window:draw(function()
    end)
end

window:close()
