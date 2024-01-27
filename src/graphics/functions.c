#include "functions.h"


int toggleFullscreen(lua_State *L) {
    ToggleFullscreen();
    return 0;
}

int setDrawColor(lua_State *L) {
    Graphics *game = luaL_checkudata(L, 1, "graphics");

    int red = luaL_checkinteger(L, 2);
    int green = luaL_checkinteger(L, 3);
    int blue = luaL_checknumber(L, 4);
    int alpha = luaL_checknumber(L, 5);

    game->drawColor.r = red;
    game->drawColor.g = green;
    game->drawColor.b = blue;
    game->drawColor.a = alpha;
    return 0;
}

int clearBackground(lua_State *L) {
    Graphics *game = luaL_checkudata(L, 1, "graphics");
    ClearBackground(game->drawColor);

    return 0;
}

int drawCircle(lua_State *L) {
    Graphics *game = luaL_checkudata(L, 1, "graphics");

    int xPos = luaL_checkinteger(L, 2);
    int yPos = luaL_checkinteger(L, 3);
    float radius = luaL_checknumber(L, 4);

    DrawCircle(xPos, yPos, radius, game->drawColor);

    return 0;
}