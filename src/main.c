#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <editline/readline.h>

#include "lua.h"
#include "util.h"
#include "user.h"

int repl(Orm64Lua *lua);

int main(int argc, const char **argv) {
  // initscr(); cbreak(); noecho();
  // nonl(); intrflush(stdscr, false); 
  // keypad(stdscr, true);

  struct stat st = {0};
  if (stat(strcat(orm64_dir(), "/config.lua"), &st) == -1) {
    orm64DirectorySetup(NULL);
  }

  User *user = createUser();
  
  printf("Welcome to Orm64! Lets login!\n");
  printf("If running for the first time, login to `guest` and use orm64.createUser(name, password) in the REPL\nOr use the orm64util CLI command.\n");
  // refresh();
  
  for (;;) {
    if (userLogin(user) != -1) {
      Orm64Lua *lua = newOrm64Lua(user);
      
      if (argc < 2) {
        int exit = repl(lua);

        if (exit) {
          break;
        }
      } else {
        const char *mode = argv[1];
        if (strcmp(mode, "script") == 0) {
          if (argc >= 2) {
            FILE *f = fopen(argv[2], "r");
            if (f != NULL) {
              const char *contents = readEntireFile(f);
              runLua(lua, contents);
              free((void*)contents);
            } else {
              printf("Failed to open file: %s\n", argv[2]);
              // refresh();
            }
          }
        } else if (strcmp(mode, "help") == 0) {
          printf("Commands: script");
          // refresh();
        }

        break;
      }

      free((void *)lua);
    } else {
      continue;
    }
  }

  free((void*)user);
  // endwin();

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
			//printf(": %s\n", lua_tostring(lua->L, -1));
    }
  }

  return 1;
}