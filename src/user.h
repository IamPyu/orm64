#pragma once

typedef struct {
  char *username;
  char *password;
} User;

#include "lua.h"

User *createUser();

int userLogin(User *user);
void setupOrm64Users(Orm64Lua *lua, User *user);