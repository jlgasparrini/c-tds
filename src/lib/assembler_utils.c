/*
 * Auxiliar functions for assembler generation.
 */

#include <stdlib.h>
#include <string.h>
#include "assembler_utils.h"

/* Return concatenation of s1 with s2. */
char* concat(char *str1, char *str2)
{
  char *result = malloc(strlen(str1) + strlen(str2) + 1);
  strcpy(result, str1);
  strcat(result, str2);
  return result;
}

/* Write the string "code" in a "file". */
inline void write_code_in_file(FILE *file, char *code)
{
  fprintf(file,"%s", code);
}

