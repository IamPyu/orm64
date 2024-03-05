#pragma once

#include <lualib.h>
#include <lauxlib.h>
#include <luajit.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
  lua_State *L;
} Orm64Lua;

#include "user.h"

Orm64Lua *newOrm64Lua(User *pUser);
void runLua(Orm64Lua *lua, const char *code);
int orm64InstallPackages(lua_State *L); 
