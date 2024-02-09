#pragma once

typedef struct {
  const char *username;
  const char *password;
} User;

User *createUser();
int userLogin(User *user);
