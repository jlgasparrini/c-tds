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
void translateGotoLabel(FILE* archivo, Code3D* code);
void translateGotoLabelCondition(FILE* archivo, Code3D* code);
void translateAssignation(FILE* archivo, Code3D* code);
void translateReturn(FILE* archivo, Code3D* code);
void translateReturnExpression(FILE* archivo, Code3D* code);
void translateOr(FILE* archivo, Code3D* code);
void translateAnd(FILE* archivo, Code3D* code);
void translateNot(FILE* archivo, Code3D* code);

/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/
void neg_Int_Translate(FILE* archivo, Code3D* code);
void add_Int_Translate(FILE* archivo, Code3D* code);
void mult_Int_Translate(FILE* archivo, Code3D* code);
void greater_IntTranslate(FILE* archivo, Code3D* code);
void greater_Eq_IntTranslate(FILE* archivo, Code3D* code);
void translateMinusInt(FILE* archivo, Code3D* code);
void translateModInt(FILE* archivo, Code3D* code);
void translateDivInt(FILE* archivo, Code3D* code);
void translateLesserInt(FILE* archivo, Code3D* code);
void translateLesserOrEqualInt(FILE* archivo, Code3D* code);
void translateEqualInt(FILE* archivo, Code3D* code);
void translateDistinctInt(FILE* archivo, Code3D* code);

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/
void greater_FloatTranslate(FILE* archivo, Code3D* code);
void greater_Eq_FloatTranslate(FILE* archivo, Code3D* code);

/******************************** PRINT OPERATION *******************************************/
void printOperation(FILE *file, Code3D *code);
#endif
