return function ()
    local graphics = require("graphics")
    local game = graphics.new(1200, 800, "My game")

    graphics.new(1200, 800, "My game")
    graphics.new(1200, 800, "My game")
    game:init()

    while not game:should_close() do
        game:draw(function ()
            print(32)
        end)
    end

    game:close()
end