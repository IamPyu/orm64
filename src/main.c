#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include "lua.h"
#include "util.h"

void repl(Orm64Lua *lua);

int main(int argc, const char **argv) {
    Orm64Lua *lua = newOrm64Lua();

    if (argc > 1) {
        const char *cmd = argv[1];
        
        if (strcmp(cmd, "run") == 0 && argc > 2) {
            char code[STRING_SIZE];
            sprintf(code, "require('%s')", argv[2]);
            runLua(lua, code);
        } else {
            printf("Invalid command. Starting a REPL\n");
            repl(lua);
        }
    } else {
        printf("Commands: run(PROGRAM)\n");
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
            runLua(lua, str);
        }
    }
}