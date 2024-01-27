#pragma once

#include <stdlib.h>
#include <string.h>
#include <luajit-2.1/lualib.h>
#include <luajit-2.1/lauxlib.h>

typedef struct {
    lua_State *L;
} Orm64Lua;

Orm64Lua *newOrm64Lua();
void runLua(Orm64Lua* lua, const char *code);