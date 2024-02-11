#pragma once

typedef struct {
  const char *username;
  const char *password;
} User;

#include "lua.h"

User *createUser();
int userLogin(User *user);
void setupOrm64Users(Orm64Lua *lua, User *user);
