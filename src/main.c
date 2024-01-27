#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include "lua.h"
#include "util.h"

void repl(Orm64Lua *lua);

int main(int argc, const char **argv) {
    Orm64Lua *lua = newOrm64Lua();

    if (argc > 2) {
        const char *cmd = argv[1];
        
        if (strcmp(cmd, "shell") == 0) {
            repl(lua);
        } else if (strcmp(cmd, "run") == 0) {
            char cmd[STRING_SIZE];
            
        }
    } else {
        printf("Commands: shell");
        repl(lua);
    }

    free((void*)lua);
    return 0;
}

void repl(Orm64Lua *lua) {
    for (;;) {
        lua_getglobal(lua->L, "orm64_options");
        lua_getfield(lua->L, -1, "prompt");
        
        char *str = readline(lua_tostring(lua->L, -1));
        add_history(str);

        if (strcmp(str, "exit") == 0) {
            break;
        } else if (strcmp(str, "help") == 0) {
            printf("%s\n", getResString(HELP_FILE));
        } else if (strcmp(str, "api") == 0) {
            printf("%s\n", getResString(API_FILE));
        } else {
            luaL_loadstring(lua->L, str);

            if (lua_pcall(lua->L, 0, 0, 0)) {
                const char *errormsg = lua_tostring(lua->L, -1);
                printf("Failed to run Lua code: %s\n", errormsg);


            }
        }
    }
}