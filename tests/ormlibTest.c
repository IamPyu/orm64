#include <stdio.h>
#include <stdlib.h>
#include <ormlib.h>

int main(int argc, const char **argv) {
  if (argc >= 3) {
    orm64_createuser(argv[1], argv[2]);
    printf("Created user: %s; with password: %s\n", argv[1], argv[2]);
  } else {
    printf("ormlibTest requires 2 parameters.\n");
  }
}