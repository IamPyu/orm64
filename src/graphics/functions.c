#include "functions.h"
#include "raylib.h"

int toggleFullscreen(lua_State *L) {
    luaL_checkudata(L, 1, "graphics");
    ToggleFullscreen();
    return 0;
}

int setTargetFPS(lua_State *L) {
    luaL_checkudata(L, 1, "graphics");
    int fps = luaL_checkinteger(L, 2);
    SetTargetFPS(fps);
    return 0;
}

int setDrawColor(lua_State *L) {
    Graphics *window = luaL_checkudata(L, 1, "graphics");

    int red = luaL_checkinteger(L, 2);
    int green = luaL_checkinteger(L, 3);
    int blue = luaL_checknumber(L, 4);
    int alpha = luaL_checknumber(L, 5);

    window->drawColor.r = red;
    window->drawColor.g = green;
    window->drawColor.b = blue;
    window->drawColor.a = alpha;

    return 0;
}

int clearBackground(lua_State *L) {
    Graphics *window = luaL_checkudata(L, 1, "graphics");
    ClearBackground(window->drawColor);

    return 0;
}

int drawCircle(lua_State *L) {
    Graphics *window = luaL_checkudata(L, 1, "graphics");

    int xPos = luaL_checkinteger(L, 2);
    int yPos = luaL_checkinteger(L, 3);
    float radius = luaL_checknumber(L, 4);

    DrawCircle(xPos, yPos, radius, window->drawColor);
    return 0;
}

int drawRect(lua_State *L) {
    Graphics *window = luaL_checkudata(L, 1, "graphics");

    int xPos = luaL_checkinteger(L, 2);
    int yPos = luaL_checkinteger(L, 3);
    int xScale = luaL_checknumber(L, 4);
    int yScale = luaL_checkinteger(L, 5);

    DrawRectangle(xPos, yPos, xScale, yScale, window->drawColor);
    return 0;
}

int isKeyDown(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsKeyDown(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}

int isKeyUp(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsKeyUp(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}
