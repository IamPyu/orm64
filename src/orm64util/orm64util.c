#include <stdio.h>
#include <stdlib.h>

#include "../orm64lib/orm64lib.h"
#include "ormutil.h"

int main(int argc, const char **argv) {
  if (argc >= 2) {
    const char *cmd = argv[1];

    if (streq(cmd, "help")) {
      printHelp();
    }

    if (streq(cmd, "newuser") && argc > 3) {
      const char *user = argv[2];
      const char *pass = argv[3];

      orm64_createuser(user, pass);
      printf("Created user: %s\n", user);
    }

    if (streq(cmd, "dir")) {
      printf("%s\n", orm64_dir());
    }
  } else {
    printHelp();
  }

  return 0;
}
