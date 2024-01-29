#include "socket.h"
#include <SDL2/SDL_net.h>

void setupOrm64Sockets(Orm64Lua *lua) { SDLNet_Init(); }
