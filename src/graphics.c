#include <raylib.h>
#include <pthread.h>
#include "graphics.h"

typedef struct {
    lua_Integer width;
    lua_Integer height;
    const char *title;
    lua_CFunction draw;
} Game;


static int games = 0;
static int newGame(lua_State *L) {
    Game *game = lua_newuserdata(L, sizeof(Game));

    luaL_getmetatable(L, "graphics");
    lua_setmetatable(L, -2);

    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    game->width = width;
    game->height = height;
    game->title = title;
    game->draw = NULL;

    games++;

    return 1;
}

static int listGames(lua_State *L) {
    lua_pushinteger(L, games);
    return 1;
}

static int initGame(lua_State *L) {
    Game *game = lua_touserdata(L, -1);
    InitWindow(game->width, game->height, game->title);
    return 1;
}

static int closeGame(lua_State *L) {
    Game *game = luaL_checkudata(L, 1, "graphics");
    
    if (WindowShouldClose()) {
        games--;
        CloseWindow();
    }
    
    return 1;
}

static int gameShouldClose(lua_State *L) {
    Game *game = luaL_checkudata(L, 1, "graphics");
    lua_pushboolean(L, (int)WindowShouldClose());
    return 1;
}

static int gameDraw(lua_State *L) {
    Game *game = luaL_checkudata(L, 1, "graphics");

    BeginDrawing();

    if (lua_gettop(L) == 2) {
        if (lua_isfunction(L, -1)) {
            lua_pcall(L, 0, 0, 0);
        }
    }

    EndDrawing();

    return 1;
}

static struct luaL_Reg graphicslib_f[] = {
    {"new", newGame},
    {"games", listGames},
    {NULL, NULL}
};

static struct luaL_Reg graphicslib_m[] = {
    {"init", initGame},
    {"close", closeGame},
    {"should_close", gameShouldClose},
    {"draw", gameDraw},
    {NULL, NULL}
};

void setupOrm64Graphics(Orm64Lua *lua) {
    luaL_newmetatable(lua->L, "graphics");
    
    lua_pushstring(lua->L, "__index");
    // lua_pushstring(lua->L, "index");
    lua_pushvalue(lua->L, -2); /* pushes the metatable */
    lua_settable(lua->L, -1);  /* metatable.__index = metatable */

    luaL_openlib(lua->L, NULL, graphicslib_m, 0);
    luaL_openlib(lua->L, "graphics", graphicslib_f, 0);
}