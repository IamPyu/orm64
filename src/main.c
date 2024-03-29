#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <editline/readline.h>

#include "lua.h"
#include "util.h"
#include "orm64lib/orm64lib.h"

int repl(Orm64Lua *lua);

int main(int argc, const char **argv) {
  struct stat st = {0};
  if (stat(strcat(orm64_dir(), "/config.lua"), &st) == -1) {
    printf("No configuration found, copy default configuration from INSTALL_DIR/etc/orm64/default to ~/.config/orm64\n");
    printf("And create ~/.config/orm64/config.lua\n");
    orm64DirectorySetup(NULL);
  }


#if defined(DEBUG_MODE)
  printf("Orm64 compiled with Debug mode!\n");
  printf("String Size: %lu\n", STRING_SIZE);
  printf("Default User: %s\n", DEFAULT_USER);
#if defined(ENABLE_BLOAT)
  printf("Bloat is enabled, featuers like users can be used.\n");
#endif

  printf("End of debug information\n\n\n");
#endif

#if defined(ENABLE_BLOAT)
  printf("Orm64 Login\n");
  printf("If running Orm64 for the first time, use `man 1 orm64util` to learn how to create a user.\n");

  #include "user.h"
  User *user = createUser();

  for (;;) {
    if (userLogin(user) != -1) {
      Orm64Lua *lua = newOrm64Lua(user);
      int exit = repl(lua);
      free((void*)lua);

      if (exit) {
        break;
      }
    } else {
      continue;
    }
  }
  free((void*)user);
#else
  Orm64Lua *lua = newOrm64Lua(NULL);
  repl(lua);
  free((void*)lua);
#endif

  return 0;
}

int repl(Orm64Lua *lua) {

#define getOption(T, t, v, n)\
  lua_getglobal(lua->L, "orm64_options");\
  lua_getfield(lua->L, -1, #n);\
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
    } else if (strcmp(str, "wiki") == 0) {
      extern void OpenURL(const char*); /* Linked with libraylib */
      OpenURL("https://gitlab.com/IamPyu/orm64/-/wikis/home"); /* Send user to online wiki */
    }
    else {
      runLua(lua, str);
    }
  }

  return 1;
}
