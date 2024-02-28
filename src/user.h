#pragma once

struct User {
  char *username;
  char *password;
};

#include "lua.h"

User *createUser();

int userLogin(User *user);
void setupOrm64Users(Orm64Lua *lua, User *user);
