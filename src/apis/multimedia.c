#include <raylib.h>
#include "multimedia.h"

static int multimediaInit(lua_State *L) {
  InitAudioDevice();
  return 0;
}

static int multimediaClose(lua_State *L) {
  CloseAudioDevice();
  return 0;
}

#include <pthread.h>
void *playSoundThread(void *vargp) {
  const char *path = (const char*)vargp;
  Sound sound = LoadSound(path);
  PlaySound(sound);
  return (void*)0;
}

static int playSound(lua_State *L) {
  const char *path = luaL_checkstring(L, 1);
  pthread_t tid;
  pthread_create(&tid, NULL, playSoundThread, (void*)path);
  
  return 0;
}

static const struct luaL_Reg multimedialib[] = {
  {"init", multimediaInit},
  {"close", multimediaClose},
  {"playSound", playSound},
  {NULL, NULL}
};

void setupOrm64Multimedia(Orm64Lua *lua) {
  luaL_openlib(lua->L, "multimedia", multimedialib, 0);
}
