#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "util.h"

/// Reads all the contents of `ptr`. If failed the function returns an empty string
/// @param ptr A pointer the the file
/// @return 
char *readEntireFile(FILE* ptr) {
    char* contents = (char*)malloc(32767 * 16);
    char ch;

    if (ptr != NULL) {
        while ((ch = fgetc(ptr)) != EOF) {
            strncat(contents, &ch, 1);
        }           
    }

    return contents;
}

char *orm64Dir() {
    char directory[32767 * 16];
    sprintf(directory, "%s/%s", getenv("HOME"), ".orm64.d/");
    
    char *p = directory;
    return p;
}


void mkdir2(const char* directory, mode_t mode) {
    struct stat st = {0};
    if (stat(directory, &st) == -1) mkdir(directory, mode);
}