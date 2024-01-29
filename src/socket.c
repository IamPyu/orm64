#include <SDL2/SDL_net.h>
#include "socket.h"

void setupOrm64Sockets(Orm64Lua *lua) {
    SDLNet_Init();
}