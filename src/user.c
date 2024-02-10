#include "user.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <editline/readline.h>

User *createUser() {
  User *user = malloc(sizeof(User));
  user->username = "";
  user->password = "";
  
  return user;
}

int userLogin(User *user) {
  const char *login = readline("User login: ");
  char userPath[STRING_SIZE];
  sprintf(userPath, "%s/home/%s", orm64Dir(), login);

  struct stat st = {0};
  if (stat(userPath, &st) != -1) {
    user->username = login;
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
    //contents[strlen(contents)-1] = '\0';

    const char *password = readline("User password: ");
    int passwordFailed = false;

      printf("up: %s, rp: %s", password, contents);

    if (strcmp(contents, password) == 0) {
      printf("Password correct.\n");
    } else {
      printf("Password incorrect.\n");
      passwordFailed = true;
    }
    
    free((void*)contents);

    if (passwordFailed) {
      return -1;
    }
  } else {
    printf("User does not have a password.\n");
  }
  
  printf("Logged into: %s\n", login);
  return 0;
}
