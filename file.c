#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void file_initialize(File * file) {
  file->size = 0;
  file->data = NULL;
}

void file_read(File * file, const char * filename) {
  FILE * fp = fopen(filename, "rb");
  assert(fp != NULL);

  fseek(fp, 0, SEEK_END);
  file->size = ftell(fp);

  file->data = (char *) realloc(file->data, file->size);
  fseek(fp, 0, SEEK_SET);

  size_t read_bytes = fread(file->data, 1, file->size, fp);
  fclose(fp);
  if (read_bytes != file->size) {
    if (feof(fp))
      printf("Error reading test.bin: unexpected end of file\n");
    else if (ferror(fp)) {
      perror("Error reading test.bin");
    }
  }
  assert(read_bytes == file->size);
}

void file_deinitialize(File * file) {
  file->size = 0;
  free(file->data);
  file->data = NULL;
}
