#pragma once
#include <dirent.h>
#include <lua.h>
#include <stdio.h>
#include <sys/stat.h>

#define STRING_SIZE 512 * sizeof(char*) /* DO NOT MODIFY THE SIZEOF OPERATOR */
#define DEFAULT_USER "guest"

#define defun(name) int name(lua_State *L);

#define true 1
#define false 0

enum ResFile { DEFAULT_CONFIG, HELP_FILE, API_FILE };

void stripFileExtension(char *fname);
char *readEntireFile(FILE *ptr);
char *getResString(enum ResFile file);

defun(orm64DirectorySetup);
