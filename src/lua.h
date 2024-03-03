#pragma once

extern "C" {
#include <lualib.h>
#include <lauxlib.h>
#include <luajit.h>
}

#include <stdlib.h>
#include <string.h>

struct Orm64Lua {
  lua_State *L;
};

#include "user.h"

Orm64Lua *newOrm64Lua(User *pUser);
void runLua(Orm64Lua *lua, const char *code);
int orm64InstallPackages(lua_State *L); 
