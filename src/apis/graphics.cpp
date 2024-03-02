#include <raylib.h>

#include "graphics.h"
#include "graphics/functions.h"

static int windows = 0;

static int newWindow(lua_State *L) {
  GraphicsWindow *window = (GraphicsWindow*)lua_newuserdata(L, sizeof(GraphicsWindow));

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
  GraphicsWindow *window = (GraphicsWindow*)lua_touserdata(L, -1);
  InitWindow(window->width, window->height, window->title);
  InitAudioDevice();
  
  return 1;
}

static int closeWindow(lua_State *L) {
  luaL_checkudata(L, 1, "graphics");

  windows--;
  CloseWindow();
  CloseAudioDevice();
  
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
    {"windows", listWindows}, 
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
    {"drawText", drawText},
    {"isKeyDown", isKeyDown},
    {"isKeyUp", isKeyUp},
	{"isKeyPressed", isKeyPressed},
    {"isKeyReleased", isKeyReleased},
    {"isMouseButtonPressed", isMouseButtonPressed},
    {"isMouseButtonReleased", isMouseButtonReleased},
    {"isMouseButtonDown", isMouseButtonDown},
    {"isMouseButtonUp", isMouseButtonUp},
    {"getMousePos", getMousePos},
	{"playSound", playSound},
	{"isGamepadButtonPressed", isGamepadButtonPressed},
	{"isGamepadButtonReleased", isGamepadButtonReleased},
	{"isGamepadButtonDown", isGamepadButtonDown},
	{"isGamepadButtonUp", isGamepadButtonUp},

    {NULL, NULL}};

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

#define defkey(x)                                                              \
  lua_pushinteger(lua->L, KEY_##x);                                            \
  lua_setfield(lua->L, -2, #x)

  defkey(A);
  defkey(B);
  defkey(C);
  defkey(D);
  defkey(E);
  defkey(F);
  defkey(G);
  defkey(H);
  defkey(I);
  defkey(J);
  defkey(K);
  defkey(L);
  defkey(M);
  defkey(N);
  defkey(O);
  defkey(P);
  defkey(Q);
  defkey(R);
  defkey(S);
  defkey(T);
  defkey(U);
  defkey(V);
  defkey(W);
  defkey(X);
  defkey(Y);
  defkey(Z);

  defkey(LEFT);
  defkey(RIGHT);
  defkey(UP);
  defkey(DOWN);

  defkey(ESCAPE);
  defkey(SPACE);
  defkey(TAB);
  defkey(CAPS_LOCK);
  defkey(ENTER);
  defkey(BACKSPACE);
  defkey(LEFT_CONTROL);
  defkey(LEFT_ALT);
  defkey(LEFT_SUPER);
  defkey(LEFT_SHIFT);
  defkey(LEFT_BRACKET);
  defkey(RIGHT_CONTROL);
  defkey(RIGHT_ALT);
  defkey(RIGHT_SUPER);
  defkey(RIGHT_SHIFT);
  defkey(RIGHT_BRACKET);

  defkey(ONE);
  defkey(TWO);
  defkey(THREE);
  defkey(FOUR);
  defkey(FIVE);
  defkey(SIX);
  defkey(SEVEN);
  defkey(EIGHT);
  defkey(NINE);
  defkey(ZERO);

  defkey(GRAVE);
  defkey(SEMICOLON);
  defkey(BACKSLASH);
  defkey(SLASH);
  defkey(APOSTROPHE);
  defkey(PERIOD);
  defkey(COMMA);
  defkey(EQUAL);
  defkey(MINUS);

  lua_newtable(lua->L);
  lua_setglobal(lua->L, "graphics_mousebutton");
  lua_getglobal(lua->L, "graphics_mousebutton");

#define defmouse(x)                   \
  lua_pushinteger(lua->L, MOUSE_BUTTON_##x); \
  lua_setfield(lua->L, -2, #x)

  defmouse(LEFT);
  defmouse(RIGHT);
  defmouse(MIDDLE);

  defmouse(SIDE);
  defmouse(BACK);
  defmouse(FORWARD);
  defmouse(EXTRA);
  
  lua_newtable(lua->L);
  lua_setglobal(lua->L, "graphics_gamepadbutton");
  lua_getglobal(lua->L, "graphics_gamepadbutton");

#define defgamepad(x)							\
  lua_pushinteger(lua->L, GAMEPAD_BUTTON_##x);	\
  lua_setfield(lua->L, -2, #x);

  // Restructure Raylib definitions
  // D-Pad
#define GAMEPAD_BUTTON_LEFT GAMEPAD_BUTTON_LEFT_FACE_LEFT
#define GAMEPAD_BUTTON_RIGHT GAMEPAD_BUTTON_LEFT_FACE_RIGHT
#define GAMEPAD_BUTTON_UP GAMEPAD_BUTTON_LEFT_FACE_UP
#define GAMEPAD_BUTTON_DOWN GAMEPAD_BUTTON_LEFT_FACE_DOWN

  // ABXY (XBOX), random shapes (PlayStation)
#define GAMEPAD_BUTTON_A GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#define GAMEPAD_BUTTON_B GAMEPAD_BUTTON_RIGHT_FACE_RIGHT
#define GAMEPAD_BUTTON_X GAMEPAD_BUTTON_RIGHT_FACE_LEFT
#define GAMEPAD_BUTTON_Y GAMEPAD_BUTTON_RIGHT_FACE_UP

  defgamepad(LEFT);
  defgamepad(RIGHT);
  defgamepad(UP);
  defgamepad(DOWN);

  defgamepad(A);
  defgamepad(B);
  defgamepad(X);
  defgamepad(Y);

  defgamepad(LEFT_TRIGGER_1);
  defgamepad(LEFT_TRIGGER_2);
  defgamepad(RIGHT_TRIGGER_1);
  defgamepad(RIGHT_TRIGGER_2);

  defgamepad(LEFT_THUMB);
  defgamepad(RIGHT_THUMB);
}
