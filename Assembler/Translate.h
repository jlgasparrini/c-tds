#ifndef Translate_H
#define Translate_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concat(char* str1, char* str2);
void writeCodeInFile(FILE* file, char* operation, char* code1, char* code2);
void writeBlank(FILE* file);

#endif
