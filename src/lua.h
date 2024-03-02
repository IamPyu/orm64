#pragma once

extern "C" {
  #include <luajit-2.1/lualib.h>
  #include <luajit-2.1/lauxlib.h>
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
