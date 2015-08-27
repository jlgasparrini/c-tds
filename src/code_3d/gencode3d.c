/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "gencode3d.h"
#include "operations_code.h"
#include "../SymbolsTable/Utils.h"

/**Constructor de la Lista de Codigos 3D*/
LCode3D* init_list_c3D()
{
    LCode3D *lcode = (LCode3D*) malloc(sizeof(LCode3D));
    lcode->codes = new_list_c3d();
    return lcode;
}

/**Metodo que agrega un Codigo 3D a la lista*/
void add_code(LCode3D *lcode3d, Code3D *code)
{
	add_list_c3d(lcode3d->codes, code);
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_code(LCode3D *lcode3d, int index)
{
    return get_list_c3d(lcode3d->codes, index);
}

/**Metodo de retorna el tamaño de la Lista*/
int code_size(LCode3D *lcode3d)
{
    return size_list_c3d(lcode3d->codes);
}

void set_code_int(LCode3D *lcode3d,int index,int param, int numb)
{
    set_list_c3d_int(lcode3d->codes,index, param, numb);
}

/**Metodo que a base de un Codigo 3D y un label, setea el codigo y lo agrega a la Lista*/
void add_code_label(LCode3D *lcode3d, Code3D *code, char *label)
{
	set_code_label(code, label);
    add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D, un Atributo y un label, setea el codigo y lo agrega a la Lista*/
void add_code_label_cond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *labelToJump)
{
	set_code_label_cond(code, attri1, labelToJump);
    add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_assignation(LCode3D *lcode3d, Attribute *attri1, Attribute *attriRes)
{
    Code3D *code;
    switch (get_attribute_type(attri1))
    {
        case Int:   code = new_code(ASSIGNATION_INT); break;
        case Float: code = new_code(ASSIGNATION_FLOAT); break;
        case Bool:  code = new_code(ASSIGNATION_BOOL); break;
        default: break;
    }
	set_c2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y un Atributo, setea el codigo y lo agrega a la Lista*/
void add_print(LCode3D *lcode3d, Code3D *code, Attribute *attr)
{
	set_c1D(code, attr);
	add_code(lcode3d, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_method_call(LCode3D *lcode3d, Code3D *code,  Attribute *attri1,  Attribute *attriRes)
{	/**Uses a copy of attr1 because the parameter passing must be by value */
    set_c2D(code, attri1, attriRes);
	add_code(lcode3d, code);
}

void add_code_externinvk(LCode3D *lcode3d, Code3D *code,char *label,  char* type)
{
	set_code_label(code, label);
    set_label(code, 2, type);
    add_code(lcode3d, code);
}

void add_param_externinvk(LCode3D *lcode3d, Code3D *code, Attribute *attr, int paramNumber)
{
    set_attribute(code, 1, attr);
    set_int(code, 2, paramNumber);
    set_null(code, 3);
    add_code(lcode3d, code);
}

/**Metodo que borra un Codigo 3D de la lista dependiendo una posicion*/
void delete_code(LCode3D *lcode3d, int index)
{
	delete_list_c3d(lcode3d->codes, index);
}

/**Prints on the screen the 3d code that contains the list lcode3d */
void show_c3D(LCode3D *lcode3d)
{
	int cantCodes = code_size(lcode3d);
 	printf("Lista de codigos de 3 direcciones:\n");
	printf("---------------------------------------------------------------------------\n");
	printf("     Operacion     |       res       |       arg1       |       arg2       \n");
	printf("---------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < cantCodes; i++)
		to_string_c3D(get_code(lcode3d, i));
}
