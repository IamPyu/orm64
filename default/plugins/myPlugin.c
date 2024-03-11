#include <stdio.h>
#include <string.h>

void orm64SetupMyPlugin() {
  for (int i = 0; i < 5; i++) {
    printf("Hello, world %d!\n", (i + 1));
  }

  printf("Orm64 Rocks!\n");

  printf("Enter anything you want (Max 256 characters): ");
  char str[256];
  fgets(str, sizeof(str), stdin);
  str[strlen(str)-1] = '\0';

  printf("You entered:\n%s\n", str);
}
