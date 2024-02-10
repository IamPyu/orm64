#include <dirent.h>
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lua.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lua.h"
#include "apis/socket.h"
#include "util.h"

#include "apis/graphics.h"

int reloadConfiguration(lua_State *L) {
  FILE *configFile = fopen(strcat(orm64Dir(), "/config.lua"), "r");

  if (configFile != NULL) {
    const char *config = readEntireFile(configFile);
    luaL_loadstring(L, config);
    if (lua_pcall(L, 0, 0, 0)) {
      const char *errormsg = lua_tostring(L, -1);
      printf("An error occured in the configuration file: %s\n", errormsg);
    }

    free((void *)config);
    fclose(configFile);
    printf("(Re)Loaded configuration\n");
  } else {
    printf("Configuration file not found.\n");
    printf("Falling back to default configuration and creating default configuration.\n");
    luaL_dostring(L, "orm64.setup_config()");
  }

  return 0;
}

void setupOrm64Core(Orm64Lua *lua);

/// Creates a `Orm64Lua`. Make sure to `free` it when done.
/// `Orm64Lua`
Orm64Lua *newOrm64Lua() {
  Orm64Lua *lua = (Orm64Lua *)malloc(sizeof(Orm64Lua));
  lua->L = luaL_newstate();
  luaL_openlibs(lua->L);

  char package_code[128];
  sprintf(package_code,
          "package.path = package.path .. ';%s/software/?/init.lua'",
          orm64Dir());
  luaL_dostring(lua->L, package_code);

  setupOrm64Core(lua);

  lua_createtable(lua->L, 0, 0);
  lua_setglobal(lua->L, "orm64_options");

  char *config = getResString(DEFAULT_CONFIG);
  luaL_dostring(lua->L, config);

  reloadConfiguration(lua->L);

  return lua;
}

int orm64GetSoftwarePath(lua_State *L) {
  char path[STRING_SIZE];
  sprintf(path, "%s/software/%s", orm64Dir(), lua_tostring(L, -1));

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

int luaCreateUser(lua_State *L) {
  const char *login = lua_tostring(L, -2);
  char *password = (char*)lua_tostring(L, -1);

  char userDirectory[STRING_SIZE];
  sprintf(userDirectory, "%s/home/%s", orm64Dir(), login);
  mkdir2(userDirectory, 0700);

  if (password != NULL) {
    char *p = userDirectory;

    FILE *file = fopen(strcat(p, "/.password"), "w");
    
    if (file != NULL) {
      fwrite(password, strlen(password), 1, file);
      fflush(file);
    }
    
    fclose(file);
  }

  return 0;
}

int orm64InstallPackages(lua_State *L) {
  lua_getglobal(L, "orm64_options");
  lua_getfield(L, -1, "packages");

  lua_pushnil(L);

  while (lua_next(L, 2)) {
    if (lua_isstring(L, -2)) {
      const char *packageName = lua_tostring(L, -2);
      if (lua_isstring(L, -1)) {
        const char *url = lua_tostring(L, -1);
        lua_pop(L, 1);

        char path[STRING_SIZE];
        sprintf(path, "%s/software/%s", orm64Dir(), packageName);
        mkdir2(path, 0700);

        chdir(path);
        char cmd[STRING_SIZE];
	
        printf("Package Info{URL: %s, PackageName: %s, Path: %s}\n", url, packageName, path);
        sprintf(cmd, 
		"git init; git remote add origin %s; git remote set-url origin %s; git branch -m main; git reset --hard; git pull origin HEAD --force", url, url);

        char fullCmd[STRING_SIZE];
        sprintf(fullCmd, "cd %s; %s", path, cmd);

        system(fullCmd); // system fixed my entire package manager lol.
      } else {
        printf("Invalid package value. It must be a string.\n");
      }
    } else {
      printf("Invalid package key. It must be a string.\n");
    }
  }

  return 0;
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

  lua_pushcfunction(lua->L, luaCreateUser);
  lua_setfield(lua->L, -2, "create_user");
  
  // External Orm64 libraries
  setupOrm64Graphics(lua); // Orm64 Graphics
  setupOrm64Sockets(lua);
}

void runLua(Orm64Lua *lua, const char *code) {
  luaL_loadstring(lua->L, code);

  if (lua_pcall(lua->L, 0, 0, 0)) {
    const char *errormsg = lua_tostring(lua->L, -1);
    printf("Failed to run Lua code: %s\n", errormsg);
  }
}
