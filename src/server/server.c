#include <stdio.h>

#include "../lua.h"
#include "../util.h"
#include "server.h"

void handleServerMessage(Server *server) {
  ServerMessage *msg = server->latestMessage;

  switch (msg->type) {
    case RUNLUA: {
      char *code = (char*)msg->args[0];
      runLua(server->lua, code);
      break;
    }

    case RUNPROGRAM: {
      char *software = (char*)msg->args[0];
      char fullCode[STRING_SIZE];
      snprintf(fullCode, STRING_SIZE, "require('%s')", software);
      runLua(server->lua, fullCode);
      break;
    } 

    default: 
      printf("Invalid ServerMessageType: %d\n", msg->type); break; 
  }
}

void sendMessageToServer(Server *server, ServerMessage msg) {
  server->latestMessage = &msg;
}
