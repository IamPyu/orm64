#pragma once

#include <sys/types.h>


// Create a directory
void mkdir2(const char *directory, mode_t mode);


// --- Orm64 ---

// Create and Orm64 User
void orm64_createuser(const char *name, const char *password);

// Return the Orm64 Directory
char *orm64_dir();
