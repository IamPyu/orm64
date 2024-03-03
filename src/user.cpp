#include "user.h"
#include "lua.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <editline/readline.h>

User *createUser() {
  User *user = new User[sizeof(User)];
  user->username = (char*)"";
  user->password = (char*)"";

  return user;
}

int userLogin(User *user) {
  const char *login = readline("User login: ");
  char userPath[STRING_SIZE];
  sprintf(userPath, "%s/home/%s", orm64_dir(), login);

  struct stat st = {0};
  if (stat(userPath, &st) != -1) {
    user->username = (char*)login;
  } else {
    printf("User '%s' does not exist. Try using the default user: %s\n", login, DEFAULT_USER);
    return -1;
  }
  
  char passwordPath[STRING_SIZE];
  strcpy(passwordPath, userPath);
  strcat(passwordPath, "/.password");
  
  if (stat(passwordPath, &st) != -1) {
    FILE *passwordFile = fopen(passwordPath, "r");
    char *contents = readEntireFile(passwordFile);
    fclose(passwordFile);
    
    const char *password = readline("User password: ");
    int passwordFailed = false;

    if (strcmp(contents, password) == 0) {
      user->password = (char*)password;
      printf("Password correct.\n");
    } else {
      printf("Password incorrect.\n");
      passwordFailed = true;
    }
    
	delete contents;

    if (passwordFailed) {
      return -1;
    }
  } else {
    printf("User does not have a password.\n");
  }
  
  printf("Logged into: %s\n", login);
  return 0;
}

User *loggedInUser;

static int refreshUser(lua_State *L) {
  char passwordPath[STRING_SIZE];
  sprintf(passwordPath, "%s/home/%s/.password", orm64_dir(), loggedInUser->username);
  FILE *file = fopen(passwordPath, "r");
  
  if (file != NULL) {
    const char *contents = readEntireFile(file);
    loggedInUser->password = (char*)contents;
    free((void*)contents);
  }

  fclose(file);
  
  return 0;
}

static int changePassword(lua_State *L) {
  const char *newPassword = luaL_checkstring(L, 1); 
  const char *oldPassword = luaL_checkstring(L, 2);
  char passwordPath[STRING_SIZE];
  sprintf(passwordPath, "%s/home/%s/.password", orm64_dir(), loggedInUser->username);
  
  FILE *file = fopen(passwordPath, "w");
  
  if (file != NULL) {
    if (strcmp(loggedInUser->password, oldPassword) == 0) {
      printf("Changed password from: '%s' to '%s'.\n", oldPassword, newPassword);
      fwrite(newPassword, strlen(newPassword), 1, file);
      fflush(file);

      refreshUser(NULL);
    } else {
      printf("Please enter your current password as a second parameter.\n");
      fwrite(loggedInUser->password, strlen(loggedInUser->password), 1, file);
    }
  }

  fclose(file);
  
  return 0;
}

static int getPassword(lua_State *L) {
  lua_pushstring(L, loggedInUser->password);
  return 1;
}

static int getUsername(lua_State *L) {
  lua_pushstring(L, loggedInUser->username);
  return 1;
}

static int getPath(lua_State *L) { 
  char path[STRING_SIZE];
  sprintf(path, "%s/home/%s", orm64_dir(), loggedInUser->username);
  lua_pushstring(L, path);
  return 1;
}

static struct luaL_Reg userlib[] = {
  {"changePassword", changePassword},
  {"getPassword", getPassword},
  {"getUsername", getUsername},
  {"refreshUser", refreshUser},
  {"getPath", getPath},
  {NULL, NULL}
};

void setupOrm64Users(Orm64Lua *lua, User *pUser) {
  loggedInUser = pUser;
  luaL_openlib(lua->L, "user", userlib, 0);
}
