#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <editline/readline.h>

#include "lua.h"
#include "util.h"
#include "user.h"
#include "orm64lib/orm64lib.h"

#include "apis/graphics.h"
#include "apis/socket.h"
#include "apis/multimedia.h"

int reloadConfiguration(lua_State *L) {
  FILE *configFile = fopen(strcat(orm64_dir(), "/config.lua"), "r");

  if (configFile != NULL) {
    const char *config = readEntireFile(configFile);
    luaL_loadstring(L, config);

    if (lua_pcall(L, 0, 0, 0)) {
      const char *errormsg = lua_tostring(L, -1);
      printf("An error occured in the configuration file: %s\n", errormsg);
    }

    free((void *)config);
    printf("(Re)Loaded configuration\n");
  } else {
    printf("Configuration file not found.\n");
    printf("Falling back to default configuration and creating default configuration.\n");
    luaL_dostring(L, "orm64.setup_config()");
  }

  fclose(configFile);
  return 0;
}

void setupOrm64Core(Orm64Lua *lua);

/* Creates a `Orm64Lua`. Make sure to delete it when done. */
Orm64Lua *newOrm64Lua(User *pUser) {
  Orm64Lua *lua = (Orm64Lua*)malloc(sizeof(Orm64Lua));
  lua->L = luaL_newstate();
  luaL_openlibs(lua->L);

#if defined(ENABLE_BLOAT)
  setupOrm64Users(lua, pUser);
#endif

  char package_code[128];
  snprintf(package_code, 128, "package.path = package.path .. ';?.lua;%s/software/?/init.lua;%s/scripts/?.lua';'", orm64_dir(), orm64_dir());


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
  snprintf(path, sizeof(path), "%s/software/%s", orm64_dir(), lua_tostring(L, -1));

  if (access(path, F_OK) == 0) {
		lua_pushstring(L, path);
  } else {
    lua_pushnil(L);
  }

  return 1;
}

int orm64LoadPlugin(lua_State *L) {
  const char *pluginName = luaL_checkstring(L, 1);
  char pluginPath[STRING_SIZE];
  snprintf(pluginPath, sizeof(pluginPath), "%s/plugins/%s.so", orm64_dir(), pluginName);

  void *handle = dlopen(pluginPath, 0);
  void (*initFunction)(void);
  char *error;

  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    lua_pushboolean(L, 0);
    return 1;
  }
  dlerror(); // Clear errors

  char initFunctionName[STRING_SIZE];
  snprintf(initFunctionName, sizeof(initFunctionName), "orm64Setup%s", pluginName);

  initFunction = (void(*)(void))dlsym(handle, initFunctionName);

  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    lua_pushboolean(L, 0);
    return 1;
  }
  initFunction();

  lua_pushboolean(L, 1);
  return 1;
}

int orm64BuildPlugins(lua_State *L) {
  char path[STRING_SIZE];
  snprintf(path, sizeof(path), "%s/plugins", orm64_dir());

  DIR *dir = opendir(path);

  struct dirent *pDirent;
  if (dir != NULL) {
    while ((pDirent = readdir(dir)) != NULL) {
      const char *fileName = pDirent->d_name;
      const char *extension = strrchr(fileName, '.');
      if (strcmp(extension, ".c") == 0) {
        char compileCommand[STRING_SIZE];

        char fileNameClone[1024];
        strncpy(fileNameClone, fileName, sizeof(fileNameClone));
        stripFileExtension(fileNameClone);

        snprintf(compileCommand,
                 sizeof(compileCommand),
                 "cc -fPIC -shared %s/plugins/%s -o %s/plugins/%s.so -I%s/include -L%s/lib -lluajit-5.1",
                 orm64_dir(),
                 fileName,
                 orm64_dir(),
                 fileNameClone,
                 LUAJIT_PREFIX,
                 LUAJIT_PREFIX
        );

        printf("Building plugin '%s' with compiled command:\n'%s'\n", fileNameClone, compileCommand);
        system(compileCommand);
      }
    }
  }

  return 0;
}

#if defined(ENABLE_BLOAT)
int luaCreateUser(lua_State *L) {
  const char *login = lua_tostring(L, -2);
  char *password = (char*)lua_tostring(L, -1);

  char userDirectory[STRING_SIZE];
  sprintf(userDirectory, "%s/home/%s", orm64_dir(), login);
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
#endif

// The core functions of Orm64
void setupOrm64Core(Orm64Lua *lua) {
  // Functions and variables under the "orm64" table
  lua_createtable(lua->L, 0, 0);
  lua_setglobal(lua->L, "orm64");

  lua_getglobal(lua->L, "orm64");
  lua_pushcfunction(lua->L, orm64DirectorySetup);
  lua_setfield(lua->L, -2, "setupConfig");

  lua_pushcfunction(lua->L, reloadConfiguration);
  lua_setfield(lua->L, -2, "reloadConfig");

  lua_pushcfunction(lua->L, orm64GetSoftwarePath);
  lua_setfield(lua->L, -2, "getSoftwarePath");

  lua_pushcfunction(lua->L, orm64LoadPlugin);
  lua_setfield(lua->L, -2, "loadPlugin");

  lua_pushcfunction(lua->L, orm64BuildPlugins);
  lua_setfield(lua->L, -2, "buildPlugins");

#if defined(ENABLE_BLOAT)
  lua_pushcfunction(lua->L, luaCreateUser);
  lua_setfield(lua->L, -2, "createUser");
#endif

  // External Orm64 libraries
  setupOrm64Graphics(lua); // Orm64 Graphics
  setupOrm64Sockets(lua);  // Orm64 Sockets
  setupOrm64Multimedia(lua); // Orm64 Multimedia
}

void runLua(Orm64Lua *lua, const char *code) {
  luaL_loadstring(lua->L, code);

  if (lua_pcall(lua->L, 0, 1, 0)) {
    const char *errormsg = lua_tostring(lua->L, -1);
    printf("Failed to run Lua code: %s\n", errormsg);
  }
}
