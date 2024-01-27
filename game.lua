return function ()
    local graphics = require("graphics")
    local game = graphics.new(660, 440, "Game")

    game:init()
    game:setTargetFPS(60)

    local y = 220
    local yVel = 0

    while not game:shouldClose() do
        yVel = yVel + 0.1
        print(yVel)
        y = y + yVel

        if y > 440 + 70 then
            y = -70
        end

        game:draw(function ()
            -- Background
            game:setDrawColor(255, 255, 255, 255)
            game:clearBackground()

            -- Shapes
            game:setDrawColor(80, 60, 90, 255)

            game:drawCircle(330, 220, 60)
            game:setDrawColor(40, 140, 200, 255)
            game:drawRect(440, y, 120, 120)
        end)
    end

    game:close()
end
