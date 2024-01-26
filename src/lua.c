#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "util.h"
#include "config.h"

/// @brief Creates a `Orm64Lua`. Make sure to `free` it when done.
/// @return `Orm64Lua`
Orm64Lua *newOrm64Lua() {
    Orm64Lua *lua = (Orm64Lua*)malloc(sizeof(Orm64Lua));
    lua->L = luaL_newstate();
    luaL_openlibs(lua->L);

    lua_createtable(lua->L, 0, 0);
    lua_setglobal(lua->L, "orm64_options");

    const char *home = getenv("HOME");
    FILE *configFile = fopen(strcat(home, "/.orm64.d/config.lua"), "r");
    
    luaL_dostring(lua->L, (const char*)src_default_lua);
    if (configFile != NULL) {
        const char *config = readEntireFile(configFile);
        luaL_dostring(lua->L, config);
        free(config);
    } else {
        printf("Not found\n");
    }
    
    return lua;
}