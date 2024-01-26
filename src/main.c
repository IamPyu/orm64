#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include <string.h>

#include "lua.h"

int main(int argc, const char **argv) {
    printf("Hello, world!\n");
    Orm64Lua *lua = newOrm64Lua();

    for (;;) {
        // lua->L
        lua_getglobal(lua->L, "orm64_options");
        lua_getfield(lua->L, -1, "prompt");
        
        char *str = readline(lua_tostring(lua->L, -1));
        add_history(str);

        if (strcmp(str, "exit") == 0) {
            break;
        } else if (strcmp(str, "help") == 0) {
            // TODO: Documentation
        } else {
            luaL_loadstring(lua->L, str);

            if (lua_pcall(lua->L, 0, 0, 0)) {
                printf("Failed to run Lua code.\n");
            }
        }
    }

    free((void*)lua);
    return 0;
}