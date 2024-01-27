#include <raylib.h>
#include <pthread.h>
#include "graphics.h"

typedef struct {
    lua_Integer width;
    lua_Integer height;
    const char *title;
    lua_CFunction draw;
    lua_CFunction __index;

    Color bgColor;

} Game;

int startGame(lua_State *L) {
    Game *game = lua_touserdata(L, -1);
    
    InitWindow(game->width, game->height, game->title);

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (game->draw != NULL)
            game->draw(L);

        EndDrawing();
    }

    CloseWindow();

    return 1;
}

int indexGameValue(lua_State *L) {
    Game *game = lua_touserdata(L, -1);

    

    return 1;
}

int newGame(lua_State *L) {
    Game *game = lua_newuserdata(L, sizeof(Game));

    game->width = 660;
    game->height = 440;
    game->title = "Game";
    game->bgColor = BLACK;
    game->draw = NULL;
    

    // lua_pushlightuserdata(L, game);

    return 1;
}



void setupOrm64Graphics(Orm64Lua *lua) {
    lua_createtable(lua->L, 0, 0);
    lua_setglobal(lua->L, "ographics");

    lua_getglobal(lua->L, "ographics");

    lua_pushcfunction(lua->L, newGame);
    lua_setfield(lua->L, -2, "new");
    lua_pushcfunction(lua->L, startGame);
    lua_setfield(lua->L, -2, "start");
}