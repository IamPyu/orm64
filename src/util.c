#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "ormlib/ormlib.h"
#include "util.h"
#include "res.h"

char *readEntireFile(FILE *ptr) {
  fseek(ptr, 0, SEEK_END); 
  long size = ftell(ptr);
  char *contents = (char *)malloc(size + 1);

  if (ptr != NULL) {
    fseek(ptr, 0, SEEK_SET); 
    fread(contents, size, 1, ptr);
  }

  return contents;
}


/// Get the contents of a resource file.
/// Resource files are from `res.h`
char *getResString(enum ResFile file) {
  char str[STRING_SIZE] = "";

  switch (file) {
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

  default:
    break;
  }

  char *p = str;
  return p;
}

int orm64DirectorySetup(lua_State *L) {
  mkdir2(orm64_dir(), 0700);
  mkdir2(strcat(orm64_dir(), "/software"), 0700);
  mkdir2(strcat(orm64_dir(), "/home"), 0700);

  /* char defaultUserPath[STRING_SIZE]; */
  /* sprintf(defaultUserPath, "/home/%s", DEFAULT_USER); */
  /* mkdir2(strcat(orm64_dir(), defaultUserPath), 0700); */

  FILE *configFile = fopen(strcat(orm64_dir(), "/config.lua"), "w");

  if (configFile != NULL) {
    char *config = getResString(DEFAULT_CONFIG);
    fwrite(config, strlen(config), 1, configFile);
  }

  fclose(configFile);

  printf("Setup new configuration. You can find it in: %s\n", orm64_dir());

  return 0;
}
