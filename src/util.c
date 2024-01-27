#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "util.h"
#include "res.h"

/// Reads all the contents of `ptr`. If failed the function returns an empty string
/// @param ptr A pointer the the file
/// @return 
char *readEntireFile(FILE* ptr) {
    char *contents = (char*)malloc(STRING_SIZE);
    char ch;

    if (ptr != NULL) {
        while ((ch = fgetc(ptr)) != EOF) {
            strncat(contents, &ch, 1);
        }           
    }

    return contents;
}

char *orm64Dir() {
    char directory[STRING_SIZE];
    sprintf(directory, "%s/%s", getenv("HOME"), ".orm64.d/");
    
    char *p = directory;
    return p;
}


void mkdir2(const char* directory, mode_t mode) {
    struct stat st = {0};
    if (stat(directory, &st) == -1) mkdir(directory, mode);
}

char *getResString(enum ResFile file) {
    char str[STRING_SIZE] = "";

    switch (file)
    {
        case DEFAULT_CONFIG: {
            char *txt = (char *)src_default_lua;
            txt[src_default_lua_len] = '\0';
            strcpy(str, txt);
            break;
        }

        case HELP_FILE: {
            char *txt = (char *)src_doc_help_md;
            txt[src_doc_help_md_len] = '\0';
            strcpy(str, txt);
            break;
        }

        case API_FILE: {
            char *txt = (char *)src_doc_api_md;
            txt[src_doc_api_md_len] = '\0';
            strcpy(str, txt);
            break;
        }

        default: break;
    }

    char *p = str;
    return p;
}