#include "../graphics.h"
#include "../../lua.h"

#include <raylib.h>

// Window
int toggleFullscreen(lua_State *L);
int setTargetFPS(lua_State *L);

// Drawing
int setDrawColor(lua_State *L);
int clearBackground(lua_State *L);
int drawCircle(lua_State *L);
int drawRect(lua_State *L);

// Input
int isKeyDown(lua_State *L);
int isKeyUp(lua_State *L);
