#pragma once

#include "../lua.h"

enum ServerMessageType {
  RUNLUA,
  RUNPROGRAM
};

typedef union {
  int v;
} Integer;

typedef union {
  float v;
} Float;

typedef struct {
  enum ServerMessageType type;
  void **args;
} ServerMessage;

typedef struct {
  Orm64Lua *lua; /* Pointer to current Orm64 lua. */
  ServerMessage *latestMessage;
} Server;


void handleServerMessage(Server *server);
void sendMessageToServer(Server *server, ServerMessage msg);
