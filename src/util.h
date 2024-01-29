#pragma once
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#define STRING_SIZE 32767 * 16

char *readEntireFile(FILE *ptr);
char *orm64Dir();
void mkdir2(const char *directory, mode_t mode);

enum ResFile { DEFAULT_CONFIG, HELP_FILE, API_FILE };

char *getResString(enum ResFile file);
