return function ()
    local function printf(text, ...)
        io.write(string.format(text, ...), io.stdout)
    end

    local graphics = require("graphics")
    local game = graphics.new(660, 440, "Game")

    game:init()
    game:toggleFullscreen()

    while not game:shouldClose() do
        game:draw(function ()
            game:setDrawColor(255, 255, 255, 255)
            game:clearBackground()
            game:setDrawColor(0, 0, 0, 255)
            game:drawCircle(330, 220, 60)
        end)
    end

    game:close()
end