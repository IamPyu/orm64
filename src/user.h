#pragma once
#include "lua.h"

typedef struct {
  const char *username;
  const char *password;
} User;

User *createUser();
int userLogin(User *user);
void setupOrm64Users(Orm64Lua *lua, User *user);
