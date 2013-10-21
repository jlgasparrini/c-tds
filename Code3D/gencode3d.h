/************************************************************************
*Define la estructura  y funciones asociadas para un generador de       *
*codigo de 3 direcciones                                              *
*************************************************************************/

#ifndef GENCODE3D_H
#define GENCODE3D_H

#include "listc3d.h"
#include "code3d.h"

typedef struct {
    ListC3D *codes;
} LCode3D;

LCode3D* initLCode3D();

int add_code(LCode3D *lcode3d, Code3D *code); 
Code3D* get_code(LCode3D *lcode3d, int index);
int codeSize(LCode3D *lcode3d);

void add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label);
void add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *label);

void add_Assignation(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes);
void add_MethodCall(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  StVariable *attriRes);
#endif
