#ifndef UTIL_STRING_H
#define UTIL_STRING_H

typedef struct {
  const char * data;
  int length;
} String;

void string_assign_empty(String * string);
void string_assign_constant_cstring(String * string, const char * cstring);

#endif
