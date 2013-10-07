/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include "gencode3d.h"
#include <stdlib.h>
#include <stdio.h>

LCode3D* initLCode3D() {
    LCode3D *new = (LCode3D*) malloc(sizeof(LCode3D));
    new->codes = newListC3D();
    return new;
}

int add_code(LCode3D *lcode3d, Code3D *code) {
        add_listC3D(lcode3d->codes, code, size_listC3D(lcodigo3d->code));
        return -1;
}

Code3D* get_code(LCode3D3D *lcode3d, int index); {
    return get_listC3D(lcodigo3d->codes, index);
}

int cantCode(LCode3D *lcode3d) {
    return size_listC3D(lcode3d->codes);
}

int add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label){
	setCodeLabel(code, label);
    add_code(lcode3d, code);
}

int add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *label){
	setCodeLabelCond(code, attri1, label);
    add_code(lcode3d, code);
}