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

/**Constructor de una Lista*/
LCode3D* initLCode3D();

/**Funcion de Escritura de la Lista*/
void add_code(LCode3D *lcode3d, Code3D *code); 

/**Funciones de Acceso a la Lista*/
Code3D* get_code(LCode3D *lcode3d, int index);
int codeSize(LCode3D *lcode3d);

/** Funciones de Escritura de la Lista de un Codigo Concreto*/
void add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label);
void add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *labelJumpTo);

void add_Assignation(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes);
void add_Print(LCode3D *lcode3d, Code3D *code, Attribute *attr);
void add_MethodCall(LCode3D *lcode3d, Code3D *code,  Attribute *attri1, Attribute *attriRes);

/**Funcion de Borrado de un Codigo de la Lista*/
void delete_code(LCode3D *lcode3d, int index);

/**Funcion de Muestreo de la Lista*/
void show3DCode(LCode3D *lcode3d);
#endif
