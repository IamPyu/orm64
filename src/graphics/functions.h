#include <raylib.h>
#include "../graphics.h"
#include "../lua.h"

int toggleFullscreen(lua_State *L);
int setTargetFPS(lua_State *L);
int setDrawColor(lua_State *L);
int clearBackground(lua_State *L);
int drawCircle(lua_State *L);
int drawRect(lua_State *L);