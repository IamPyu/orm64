#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <spawn.h>

#include "lua.h"
#include "util.h"
#include "graphics.h"

int reloadConfiguration(lua_State *L) {
    FILE *configFile = fopen(strcat(orm64Dir(), "config.lua"), "r");
    
    if (configFile != NULL) {
        const char *config = readEntireFile(configFile);
        
        luaL_loadstring(L, config);
        if (lua_pcall(L, 0, 0, 0)) {
            printf("An error occured in the configuration file\n");
        }

        free((void *)config);
        printf("(Re)Loaded configuration\n");
    } else {
        printf("Configuration file not found.\n");
        printf("To create your configuration folder run: orm64.setup_config()\n");
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

    char *config = getResString(DEFAULT_CONFIG);
    luaL_dostring(lua->L, config);

    reloadConfiguration(lua->L);
    
    return lua;
}

int orm64DirectorySetup(lua_State *L) {
    mkdir2(orm64Dir(), 0700);
    mkdir2(strcat(orm64Dir(), "software"), 0700);

    FILE *configFile = fopen(strcat(orm64Dir(), "config.lua"), "w");

    if (configFile != NULL) {
        char *config = getResString(DEFAULT_CONFIG);
        fwrite(config, strlen(config), 1, configFile);
    }

    printf("Setup new configuration. You can find it in: %s\n", orm64Dir());

    return 1;
}

int orm64GetSoftwarePath(lua_State *L) {
    char path[STRING_SIZE];
    sprintf(path, "%s%s/%s", orm64Dir(), "software", lua_tostring(L, -1));

    if (access(path, F_OK) == 0) {
        DIR *directory = opendir(path);
        if (directory != NULL) {
            lua_pushstring(L, path);
        } else {
            lua_pushnil(L);
        }
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int orm64InstallPackages(lua_State *L) {
    lua_getglobal(L, "orm64_options");
    lua_getfield(L, -1, "packages");

    while (lua_next(L, -1) != 0) {
        if (lua_isstring(L, -2)) {
            const char *key = lua_tostring(L, -2);
            if (lua_isstring(L, -2)) {
                const char *value = lua_tostring(L, -1);

                char path[STRING_SIZE];
                sprintf(path, "%ssoftware/%s", orm64Dir(), key);
                mkdir2(path, 0700);

                printf("key: %s, value: %s, path: %s\n", key, value, path);
                chdir(path);
                system("pwd");

            } else {
                printf("Invalid package value. It must be a string.\n");
            }
        } else {
            printf("Invalid package key. It must be a string.\n");
        }
    }

    return 1;
}

// The core functions of Orm64
void setupOrm64Core(Orm64Lua *lua) {
    // Functions and variables under the "orm64" table
    lua_createtable(lua->L, 0, 0);
    lua_setglobal(lua->L, "orm64");

    lua_getglobal(lua->L, "orm64");
    lua_pushcfunction(lua->L, orm64DirectorySetup);  
    lua_setfield(lua->L, -2, "setup_config");

    lua_pushcfunction(lua->L, reloadConfiguration);
    lua_setfield(lua->L, -2, "reload_config");

    lua_pushcfunction(lua->L, orm64GetSoftwarePath);
    lua_setfield(lua->L, -2, "get_software_path");

    lua_pushcfunction(lua->L, orm64InstallPackages);
    lua_setfield(lua->L, -2, "install_packages");

    // External Orm64 libraries
    setupOrm64Graphics(lua); // Orm64 Graphics
}

void runLua(Orm64Lua *lua, const char *code) {
    luaL_loadstring(lua->L, code);

    if (lua_pcall(lua->L, 0, 0, 0)) {
        const char *errormsg = lua_tostring(lua->L, -1);
        printf("Failed to run Lua code: %s\n", errormsg);
    }
}
