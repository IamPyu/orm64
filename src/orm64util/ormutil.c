#include <stdio.h>
#include <string.h>

#include "ormutil.h"

/* Private utilites */

void print(const char *str) {
  if (str != NULL) {
    printf("%s\n", str);
  } else {
    printf("\n");
  }
}

/* ormutil.h functions */

int streq(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) {
        return 1;
    }
    return 0;
}

void printHelp() {
    print("Commands:");

    print("help - Prints this message.");
    print("newuser - Creates a user with ARG1 and ARG2.");
    print("dir - Prints out the Orm64 directory.");
}
