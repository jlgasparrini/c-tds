/*
 * Auxiliar functions for assembler generation.
 */

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdio.h>

/* Return concatenation of s1 with s2. */
char* concat(char*, char*);

/* Write the string in a file. */
void write_code_in_file(FILE*, char*);

#endif
