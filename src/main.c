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
  if (stat(strcat(orm64_dir(), "/config.lua"), &st) == -1) {
    orm64DirectorySetup(NULL);
  }

  #if defined(DEBUG_MODE)
  printf("Orm64 compiled with Debug mode!\n");
  printf("String Size: %lu\n", STRING_SIZE);
  printf("Default User: %s\n", DEFAULT_USER);
  printf("End of debug information\n");
  #endif
  
  User *user = createUser();
  
  printf("Welcome to Orm64! Lets login!\n");
  printf("If running for the first time, login to `guest` and use orm64.createUser(name, password) in the REPL\nOr use the orm64util CLI command.\n");
  
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
            }
          }
        } else if (strcmp(mode, "help") == 0) {
          printf("Commands: script");
        }
        break;
      }

      free((void*)lua);
    } else {
      continue;
    }
  }

  free((void*)user);

  return 0;
}

int repl(Orm64Lua *lua) {

#define getOption(T, t, v, x)					\
  lua_getglobal(lua->L, "orm64_options");		\
  lua_getfield(lua->L, -1, #x);					\
  T v = lua_to##t (lua->L, -1)
  
  getOption(const int, boolean, showMessages, show_messages);
  getOption(const char*, string, startupMessage, startup_message);
  getOption(const char*, string, exitMessage, exit_message);
  getOption(const char*, string, prompt, prompt);
  
  if (showMessages) {
	printf("%s\n", startupMessage);
  }

  for (;;) {
    const char *str = (const char*)readline(prompt);
    add_history(str);

    if (strcmp(str, "exit") == 0) {
	  if (showMessages) {
		printf("%s\n", exitMessage);
	  }
      break;
    }
    else if (strcmp(str, "help") == 0) {
      printf("%s\n", getResString(HELP_FILE));
    }
    else if (strcmp(str, "api") == 0) {
      printf("%s\n", getResString(API_FILE));
    }
    else if (strcmp(str, "logout") == 0) {
	  if (showMessages) {
		printf("%s\n", exitMessage);
	  }
      return 0;
    }
    else {
      runLua(lua, str);
    }
  }

  return 1;
}
