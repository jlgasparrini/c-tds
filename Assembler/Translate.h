#ifndef Translate_H
#define Translate_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Code3D/gencode3d.h"

/* Writing methods */
char* concat(char* str1, char* str2);
void writeCodeInFile(FILE* file, char* operation, char* code1, char* code2);
void writeBlank(FILE* file);

/* Getters methods */
char* value(Code3D* code);
char* offset(Code3D* code, int param);

/* Methods for translation to assembly code */
void load_Const_Translate(FILE* file, Code3D* code);
void translateGotoLabel(FILE* file, Code3D* code);
void translateGotoLabelCondition(FILE* file, Code3D* code);
void translateAssignation(FILE* file, Code3D* code);
void translateReturn(FILE* file, Code3D* code);
void translateReturnExpression(FILE* file, Code3D* code);
void translateOr(FILE* file, Code3D* code);
void translateAnd(FILE* file, Code3D* code);
void translateNot(FILE* file, Code3D* code);
void printOperation(FILE *file, Code3D *code);
void writeLabel(FILE *file, Code3D *code);
void translateParamAssign(FILE *file, Code3D *code);
void translateLoadArray(FILE *file, Code3D *code);
void translateGotoMethod(FILE *file, Code3D *code);

/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/
void neg_Int_Translate(FILE* file, Code3D* code);
void add_Int_Translate(FILE* file, Code3D* code);
void mult_Int_Translate(FILE* file, Code3D* code);
void greater_IntTranslate(FILE* file, Code3D* code);
void greater_Eq_IntTranslate(FILE* file, Code3D* code);
void translateMinusInt(FILE* file, Code3D* code);
void translateModInt(FILE* file, Code3D* code);
void translateDivInt(FILE* file, Code3D* code);
void translateLesserInt(FILE* file, Code3D* code);
void translateLesserOrEqualInt(FILE* file, Code3D* code);
void translateEqualInt(FILE* file, Code3D* code);
void translateDistinctInt(FILE* file, Code3D* code);

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/
void neg_Float_Translate(FILE* file, Code3D* code);
void eq_FloatTranslate(FILE* file, Code3D* code);
void dist_FloatTranslate(FILE* file, Code3D* code);
void greater_FloatTranslate(FILE* file, Code3D* code);
void greater_Eq_FloatTranslate(FILE* file, Code3D* code);
void translateLesserOrEqualFloat(FILE *file, Code3D* code);
void translateLesserFloat(FILE *file, Code3D* code);
void translateDivFloat(FILE* file, Code3D* code);
void translateMultFloat(FILE* file, Code3D* code);
void translateAddFloat(FILE* file, Code3D* code);
void translateMinusFloat(FILE* file, Code3D* code);

#endif
