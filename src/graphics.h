#pragma once
#include <raylib.h>
#include "lua.h"

typedef struct {
    const char *title;
    int width;
    int height;

    lua_CFunction draw;
    Color drawColor;    
} Graphics;

void setupOrm64Graphics(Orm64Lua *lua);