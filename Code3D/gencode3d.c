/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../SymbolsTable/Attribute.h"
#include "listc3d.h"
#include "gencode3d.h"

LCode3D* initLCode3D() 
{
    LCode3D *new = (LCode3D*) malloc(sizeof(LCode3D));
    (*new).codes = newListC3D();
    return new;
}

void add_code(LCode3D *lcode3d, Code3D *code) 
{
	add_listC3D((*lcode3d).codes, code, size_listC3D((*lcode3d).codes));
}

Code3D* get_code(LCode3D *lcode3d, int index)
{
    return get_listC3D((*lcode3d).codes, index);
}

int codeSize(LCode3D *lcode3d) 
{
    return size_listC3D((*lcode3d).codes);
}

void add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label)
{
	setCodeLabel(code, label);
    add_code(lcode3d, code);
}

void add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *label)
{
	setCodeLabelCond(code, attri1, label);
    add_code(lcode3d, code);
}

void add_Assignation(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes)
{
	setCode2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

void add_Print(LCode3D *lcode3d, Code3D *code, Attribute *attr)
{
	setCode1D(code, attr);
	add_code(lcode3d, code);
}

void add_MethodCall(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  StVariable *attriRes)
{	/* Uses a copy of attr1 because the parameter passing must be by value */
	Attribute *aux = createVariable(getID(attri1), getAttributeType(attri1));
	if (getAttributeType(attri1) == Int)
		setIntVal(aux, getIntVal(attri1));		
	if (getAttributeType(attri1) == Float)
		setFloatVal(aux,getFloatVal(attri1));		
	if (getAttributeType(attri1) == Bool)
		setBoolVal(aux, getBoolVal(attri1));		

	setAttribute(code, 1, aux);
	setVariable(code, 2, attriRes);
	setNull(code, 3);
	add_code(lcode3d, code);
}

/* Prints on the screen the 3d code that contains the list lcode3d */
void show3DCode(LCode3D *lcode3d)
{
	int cantCodes = codeSize(lcode3d);
    int i;
 	printf("Lista de codigos de 3 direcciones:\n");
	printf("---------------------------------------------------------------------------\n");
	printf("     Operacion     |       res       |       arg1       |       arg2       \n");
	printf("---------------------------------------------------------------------------\n");
    for (i = 0; i < cantCodes; i++)
		toString3DC(get_code(lcode3d, i));
}
