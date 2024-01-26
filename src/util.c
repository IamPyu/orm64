#include <string.h>
#include <stdlib.h>
#include "util.h"

/// @brief Reads all the contents of `ptr`. If failed the function returns an empty string
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