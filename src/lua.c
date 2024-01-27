#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lua.h"
#include "util.h"
#include "res.h"

int reloadConfiguration(lua_State *L) {
    FILE *configFile = fopen(strcat(orm64Dir(), "config.lua"), "r");
    
    if (configFile != NULL) {
        const char *config = readEntireFile(configFile);
        luaL_dostring(L, config);
        free((void *)config);
        printf("(Re)Loaded configuration\n");
    } else {
        printf("Configuration file not found.\n");
        printf("To create your configuration folder run: orm64.setupConfig()\n");
        printf("Falling back to default configuration.\n");
    }

    return 0;
}

void setupOrm64Core(Orm64Lua *lua);

/// @brief Creates a `Orm64Lua`. Make sure to `free` it when done.
/// @return `Orm64Lua`
Orm64Lua *newOrm64Lua() {
    Orm64Lua *lua = (Orm64Lua*)malloc(sizeof(Orm64Lua));
    lua->L = luaL_newstate();
    luaL_openlibs(lua->L);

    char package_code[128];
    sprintf(package_code, "package.path = package.path .. ';%ssoftware/?/init.lua;?.lua'", orm64Dir());
    luaL_dostring(lua->L, package_code);

    setupOrm64Core(lua);

    lua_createtable(lua->L, 0, 0);
    lua_setglobal(lua->L, "orm64_options");


    char *config = (char*)src_default_lua;
    config[src_default_lua_len] = '\0';    
    luaL_dostring(lua->L, config);

    reloadConfiguration(lua->L);
    
    return lua;
}

int orm64DirectorySetup(lua_State *L) {
    mkdir2(orm64Dir(), 0700);
    mkdir2(strcat(orm64Dir(), "software"), 0700);

    FILE *configFile = fopen(strcat(orm64Dir(), "config.lua"), "w");

    if (configFile != NULL) {
        char *config = (char *)src_default_lua;
        config[src_default_lua_len] = '\0';
        fwrite(config, src_default_lua_len, 1, configFile);
    }

    printf("Setup new configuration. You can find it in: %s\n", orm64Dir());

    return 0;
}

// The core functions of Orm64
void setupOrm64Core(Orm64Lua *lua) {
    
    lua_createtable(lua->L, 0, 0);
    lua_setglobal(lua->L, "orm64");
    lua_getglobal(lua->L, "orm64");


    lua_pushcfunction(lua->L, orm64DirectorySetup);  
    lua_setfield(lua->L, -2, "setupConfig");

    lua_pushcfunction(lua->L, reloadConfiguration);
    lua_setfield(lua->L, -2, "reloadConfiguration");
}