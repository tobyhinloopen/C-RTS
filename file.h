#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct {
  char * data;
  size_t size;
} File;

void file_initialize(File *);
void file_read(File *, const char * filename);
void file_deinitialize(File *);

#endif
