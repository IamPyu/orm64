return function ()
    local graphics = require("graphics")
    local game = graphics.new(660, 440, "Game")

    game:init()
    game:setTargetFPS(60)

    local x = 330
    local y = 220
    local speed = 5

    local function moveX( n)
        local b = (n == true and speed or -speed)
        x = x + b
    end
    local function moveY( n)
        local b = (n == true and speed or -speed)
        y = y + b
    end

    while not game:shouldClose() do
        if game:isKeyDown(graphics_keys.KEY_D) then
           moveX(true)
        end
        if game:isKeyDown(graphics_keys.KEY_A) then
            moveX(false)
        end
        if game:isKeyDown(graphics_keys.KEY_S) then
            moveY(true)
        end
        if game:isKeyDown(graphics_keys.KEY_W) then
            moveY(false)
        end

        game:draw(function ()
            -- Background
            game:setDrawColor(255, 255, 255, 255)
            game:clearBackground()

            -- Shapes
            game:setDrawColor(80, 60, 90, 255)
            game:drawCircle(x, y, 60)
        end)
    end

    game:close()
end
