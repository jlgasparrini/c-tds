/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "gencode3d.h"
#include "codespecs.h"

/**Constructor de la Lista de Codigos 3D*/
LCode3D* initLCode3D() 
{
    LCode3D *new = (LCode3D*) malloc(sizeof(LCode3D));
    (*new).codes = newListC3D();
    return new;
}

/**Metodo que agrega un Codigo 3D a la lista*/
void add_code(LCode3D *lcode3d, Code3D *code) 
{
	add_listC3D((*lcode3d).codes, code, size_listC3D((*lcode3d).codes));
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_code(LCode3D *lcode3d, int index)
{
    return get_listC3D((*lcode3d).codes, index);
}

/**Metodo de retorna el tamaño de la Lista*/
int codeSize(LCode3D *lcode3d) 
{
    return size_listC3D((*lcode3d).codes);
}
                                
void set_code_int(LCode3D *lcode3d,int index,int param, int numb)
{
    set_listC3D_int(lcode3d->codes,index, param, numb);
}

/**Metodo que a base de un Codigo 3D y un label, setea el codigo y lo agrega a la Lista*/
void add_CodeLabel(LCode3D *lcode3d, Code3D *code, char *label)
{
	setCodeLabel(code, label);
    add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D, un Atributo y un label, setea el codigo y lo agrega a la Lista*/
void add_CodeLabelCond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *labelToJump)
{
	setCodeLabelCond(code, attri1, labelToJump);
    add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_Assignation(LCode3D *lcode3d, Attribute *attri1, Attribute *attriRes)
{
    Code3D *code;
    if (getAttributeType(attri1) == Int)
        code = newCode(ASSIGNATION_INT);  
    if (getAttributeType(attri1) == Float)
        code = newCode(ASSIGNATION_FLOAT);  
    if (getAttributeType(attri1) == Bool)
        code = newCode(ASSIGNATION_BOOL);  
	setCode2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y un Atributo, setea el codigo y lo agrega a la Lista*/
void add_Print(LCode3D *lcode3d, Code3D *code, Attribute *attr)
{
	setCode1D(code, attr);
	add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_MethodCall(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes)
{	/**Uses a copy of attr1 because the parameter passing must be by value */
    setCode2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

void add_CodeExternInvk(LCode3D *lcode3d, Code3D *code,char *label,  char* type)
{
	setCodeLabel(code, label);
    setLabel(code, 2, type);
    add_code(lcode3d, code);
}

/**Metodo que borra un Codigo 3D de la lista dependiendo una posicion*/
void delete_code(LCode3D *lcode3d, int index)
{
	delete_listC3D((*lcode3d).codes, index);
}

/**Prints on the screen the 3d code that contains the list lcode3d */
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
