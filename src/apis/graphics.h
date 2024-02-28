#pragma once
#include "../lua.h"
#include <raylib.h>

struct GraphicsWindow {
  const char *title;
  int width;
  int height;

  lua_CFunction draw;
  Color drawColor;
};

void setupOrm64Graphics(Orm64Lua *lua);
