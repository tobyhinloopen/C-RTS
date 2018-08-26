#include "./string.h"
#include <string.h>

void string_assign_constant_cstring(String * string, const char * cstring) {
  string->length = strlen(cstring);
  string->data = cstring;
}
