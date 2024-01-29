#include <raylib.h>
#include "graphics.h"
#include "graphics/functions.h"

static int windows = 0;
static int newWindow(lua_State *L) {
    Graphics *window = lua_newuserdata(L, sizeof(Graphics));

    luaL_getmetatable(L, "graphics");
    lua_setmetatable(L, -2);

    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    const char *title = luaL_checkstring(L, 3);

    window->width = width;
    window->height = height;
    window->title = title;
    window->drawColor = BLACK;
    window->draw = NULL;

    windows++;

    return 1;
}

static int listWindows(lua_State *L) {
    lua_pushinteger(L, windows);
    return 1;
}

static int initWindow(lua_State *L) {
    Graphics *window = lua_touserdata(L, -1);
    InitWindow(window->width, window->height, window->title);
    InitAudioDevice();

    return 1;
}

static int closeWindow(lua_State *L) {
    luaL_checkudata(L, 1, "graphics");
    
    if (WindowShouldClose()) {
        windows--;
        CloseWindow();
    }
    
    return 1;
}

static int windowShouldClose(lua_State *L) {
    luaL_checkudata(L, 1, "graphics");
    lua_pushboolean(L, (int)WindowShouldClose());
    return 1;
}

static int windowDraw(lua_State *L) {
    luaL_checkudata(L, 1, "graphics");
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
    {"new", newWindow},
    {"games", listWindows},
    {NULL, NULL}
};

static struct luaL_Reg graphicslib_m[] = {
    // Core functions
    {"init", initWindow},
    {"close", closeWindow},
    {"draw", windowDraw},
    {"shouldClose", windowShouldClose},
    // All the other functions
    {"toggleFullscreen", toggleFullscreen},
    {"setTargetFPS", setTargetFPS},
    {"setDrawColor", setDrawColor},
    {"clearBackground", clearBackground},
    {"drawCircle", drawCircle},
    {"drawRect", drawRect},
    {"isKeyDown", isKeyDown},
    {"isKeyUp", isKeyUp},

    {NULL, NULL}
};

void setupOrm64Graphics(Orm64Lua *lua) {
    luaL_newmetatable(lua->L, "graphics");
    
    lua_pushstring(lua->L, "__index");
    lua_pushvalue(lua->L, -2);
    lua_settable(lua->L, -1);

    luaL_openlib(lua->L, NULL, graphicslib_m, 0);
    luaL_openlib(lua->L, "graphics", graphicslib_f, 0);

    // boilerplate 
    lua_newtable(lua->L);
    lua_setglobal(lua->L, "graphics_keys");
    lua_getglobal(lua->L, "graphics_keys");
    
    #define defkey(x) lua_pushinteger(lua->L, KEY_##x); lua_setfield(lua->L, -2, #x)
   
    defkey(A);defkey(B);defkey(C);defkey(D);defkey(E);defkey(F);defkey(G);defkey(H);defkey(I);
    defkey(J);defkey(K);defkey(L);defkey(M);defkey(N);defkey(O);defkey(P);defkey(Q);defkey(R);
    defkey(S);defkey(T);defkey(U);defkey(V);defkey(W);defkey(X);defkey(Y);defkey(Z);
    
    defkey(LEFT);
    defkey(RIGHT);
    defkey(UP);
    defkey(DOWN);

    defkey(ESCAPE); defkey(TAB); defkey(CAPS_LOCK);
    defkey(LEFT_CONTROL); defkey(LEFT_ALT); defkey(LEFT_SUPER); defkey(LEFT_SHIFT); defkey(LEFT_BRACKET);
    defkey(RIGHT_CONTROL); defkey(RIGHT_ALT); defkey(RIGHT_SUPER); defkey(RIGHT_SHIFT); defkey(RIGHT_BRACKET);
    
    defkey(ONE); defkey(TWO); defkey(THREE); defkey(FOUR); defkey(FIVE);
    defkey(SIX); defkey(SEVEN); defkey(EIGHT); defkey(NINE); defkey(ZERO);

    defkey(GRAVE);defkey(SEMICOLON);defkey(BACKSLASH);defkey(SLASH);defkey(APOSTROPHE);
    defkey(PERIOD);defkey(COMMA);defkey(EQUAL);defkey(MINUS);
}
