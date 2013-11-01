#ifndef Translate_H
#define Translate_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Code3D/gencode3d.h"

/**Metodos de escritura*/
char* concat(char* str1, char* str2);
void writeCodeInFile(FILE* file, char* operation, char* code1, char* code2);
void writeBlank(FILE* file);

/**Metodos de obtencion de informacion*/
char* value(Code3D* code);
char* offset(Code3D* code, int param);

/**Metodos de traduccion*/
void load_Const_Translate(FILE* archivo, Code3D* code);
void neg_Int_Translate(FILE* archivo, Code3D* code);
void add_Int_Translate(FILE* archivo, Code3D* code);
void mult_Int_Translate(FILE* archivo, Code3D* code);
void greater_IntTranslate(FILE* archivo, Code3D* code);
void greater_FloatTranslate(FILE* archivo, Code3D* code);
void greater_Eq_IntTranslate(FILE* archivo, Code3D* code);
void greater_Eq_FloatTranslate(FILE* archivo, Code3D* code);

#endif
