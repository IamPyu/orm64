return function ()
    local graphics = require("graphics")
    local game = graphics.new(1200, 800, "My game")

    game:init()

    while not game:should_close() do
        
    end

    game:close()
end