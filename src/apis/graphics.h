#pragma once
#include "../lua.h"
#include <raylib.h>

typedef struct {
  const char *title;
  int width;
  int height;

  lua_CFunction draw;
  Color drawColor;
} GraphicsWindow;

void setupOrm64Graphics(Orm64Lua *lua);
