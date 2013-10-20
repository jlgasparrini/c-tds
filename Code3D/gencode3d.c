/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "listc3d.h"
#include "gencode3d.h"

LCode3D* initLCode3D() {
    LCode3D *new = (LCode3D*) malloc(sizeof(LCode3D));
    (*new).codes = newListC3D();
    return new;
}

int add_code(LCode3D *lcode3d, Code3D *code) {
        add_listC3D((*lcode3d).codes, code, size_listC3D((*lcode3d).codes));
        return -1;
}

Code3D* get_code(LCode3D *lcode3d, int index) {
    return get_listC3D((*lcode3d).codes, index);
}

int cantCode(LCode3D *lcode3d) {
    return size_listC3D((*lcode3d).codes);
}

void add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label){
	setCodeLabel(code, label);
    add_code(lcode3d, code);
}

void add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *label){
	setCodeLabelCond(code, attri1, label);
    add_code(lcode3d, code);
}

void add_Assignation(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes){
	setCode2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

void add_MethodCall(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  StVariable *attriRes){	
	setAttribute(code, 1, attri1);
	setVariable(code, 2, attriRes);
	setNull(code, 3);
	add_code(lcode3d, code);
}

