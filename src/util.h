#pragma once
#include <dirent.h>
#include <lua.h>
#include <stdio.h>
#include <sys/stat.h>

#include "ormlib/ormlib.h"

#define STRING_SIZE 512 * sizeof(char*)
#define DEFAULT_USER "guest"

#define defun(name) int name(lua_State *L);

#define true 1
#define false 0

char *readEntireFile(FILE *ptr);

enum ResFile { DEFAULT_CONFIG, HELP_FILE, API_FILE };

char *getResString(enum ResFile file);
defun(orm64DirectorySetup);
