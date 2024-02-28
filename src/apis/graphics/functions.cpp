#include <raylib.h>
#include "functions.h"

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
  GraphicsWindow *window = (GraphicsWindow*)luaL_checkudata(L, 1, "graphics");

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
  GraphicsWindow *window = (GraphicsWindow*)luaL_checkudata(L, 1, "graphics");
  ClearBackground(window->drawColor);

  return 0;
}

int drawCircle(lua_State *L) {
  GraphicsWindow *window = (GraphicsWindow*)luaL_checkudata(L, 1, "graphics");

  int xPos = luaL_checkinteger(L, 2);
  int yPos = luaL_checkinteger(L, 3);
  float radius = luaL_checknumber(L, 4);

  DrawCircle(xPos, yPos, radius, window->drawColor);
  return 0;
}

int drawRect(lua_State *L) {
  GraphicsWindow *window = (GraphicsWindow*)luaL_checkudata(L, 1, "graphics");

  int xPos = luaL_checkinteger(L, 2);
  int yPos = luaL_checkinteger(L, 3);
  int xScale = luaL_checknumber(L, 4);
  int yScale = luaL_checkinteger(L, 5);

  DrawRectangle(xPos, yPos, xScale, yScale, window->drawColor);
  return 0;
}

int drawText(lua_State *L) {
  GraphicsWindow *window = (GraphicsWindow*)luaL_checkudata(L, 1, "graphics");

  const char *text = luaL_checkstring(L, 2);
  int xPos = luaL_checkinteger(L, 3);
  int yPos = luaL_checkinteger(L, 4);
  int size = luaL_checkinteger(L, 5);

  DrawText(text, xPos, yPos, size, window->drawColor);
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

int isMouseButtonPressed(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsMouseButtonPressed(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}

int isMouseButtonReleased(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsMouseButtonReleased(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}

int isMouseButtonDown(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsMouseButtonDown(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}

int isMouseButtonUp(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");
  int key = luaL_checkinteger(L, 2);

  if (IsMouseButtonUp(key)) {
    lua_pushboolean(L, 1);
  } else {
    lua_pushboolean(L, 0);
  }

  return 1;
}

int getMousePos(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");

  int x = GetMouseX();
  int y = GetMouseY();

  lua_pushinteger(L, (lua_Integer)x);
  lua_pushinteger(L, (lua_Integer)y);

  return 2;
}
