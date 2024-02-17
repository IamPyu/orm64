#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <editline/readline.h>

#include "lua.h"
#include "util.h"
#include "user.h"

int repl(Orm64Lua *lua);

int main(int argc, const char **argv) {
  struct stat st = {0};
  if (stat(strcat(orm64Dir(), "/config.lua"), &st) == -1) {
    orm64DirectorySetup(NULL);    
  }

  User *user = createUser();
  
  printf("Welcome to Orm64! Lets login!\n");
  printf("If running for the first time, login to `guest` and use orm64.createUser(name, password) in the REPL\n");
  
  while (1) {
    if (userLogin(user) != -1) {
      Orm64Lua *lua = newOrm64Lua(user);
      int exit = repl(lua);
      free((void *)lua);
      
      if (exit) {
	break;
      }      
    } else {
      continue;
    }
  }

  free((void*)user);
  return 0;
}

int repl(Orm64Lua *lua) {
  lua_getglobal(lua->L, "orm64_options");
  lua_getfield(lua->L, -1, "show_startup_message");
  int showStartupMessage = lua_toboolean(lua->L, -1);

  if (showStartupMessage) {
    lua_getglobal(lua->L, "orm64_options");
    lua_getfield(lua->L, -1, "startup_message");
    printf("%s\n", lua_tostring(lua->L, -1));
  }

  for (;;) {
    lua_getglobal(lua->L, "orm64_options");
    lua_getfield(lua->L, -1, "prompt");

    char *str = readline(lua_tostring(lua->L, -1));
    add_history(str);

    if (strcmp(str, "exit") == 0) {
      lua_getglobal(lua->L, "orm64_options");
      lua_getfield(lua->L, -1, "exit_message");
      printf("%s\n", lua_tostring(lua->L, -1));
      break;
    }
    else if (strcmp(str, "help") == 0) {
      printf("%s\n", getResString(HELP_FILE));
    }
    else if (strcmp(str, "api") == 0) {
      printf("%s\n", getResString(API_FILE));
    }
    else if (strcmp(str, "logout") == 0) {
      return 0;
    }
    else {
      runLua(lua, str);
    }
  }

  return 1;
}
