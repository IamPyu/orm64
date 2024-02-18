#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "ormlib.h"
#include "../util.h"

void mkdir2(const char *directory, mode_t mode) {
  struct stat st = {0};
  if (stat(directory, &st) == -1)
    mkdir(directory, mode);
}

// --- Orm64 ---

char *orm64_dir() {
  char directory[STRING_SIZE];
  sprintf(directory, "%s/%s", getenv("HOME"), ".config/orm64");
  
  char *p = directory;
  return p;
}

void orm64_createuser(const char *login, const char *password) {
  char userDirectory[STRING_SIZE];
  sprintf(userDirectory, "%s/home/%s", orm64_dir(), login);
  mkdir2(userDirectory, 0700);

  if (password != NULL) {
    char *p = userDirectory;

    FILE *file = fopen(strcat(p, "/.password"), "w");
    
    if (file != NULL) {
      fwrite(password, strlen(password), 1, file);
      fflush(file);
    }
    
    fclose(file);
  }
}
