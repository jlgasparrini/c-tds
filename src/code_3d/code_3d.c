/*
 * Code 3d implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "code_3d.h"

#define CODE_NULL    -1
#define CODE_ATTRI    0
#define CODE_LABEL    1
#define CODE_INT      2
#define CODE_FLOAT    3
#define CODE_BOOL     4

/* Code 3d constructor. */
Code3D* newCode(int comm)
{
    Code3D *new = (Code3D*) malloc(sizeof(Code3D));
    (*new).param1 = (Param*) malloc(sizeof(Param));
    (*new).param2 = (Param*) malloc(sizeof(Param));
    (*new).param3 = (Param*) malloc(sizeof(Param));
	(*new).param1->type = CODE_NULL;
	(*new).param2->type = CODE_NULL;
	(*new).param3->type = CODE_NULL;
    (*new).command = comm;
    return new;
}

/**Metodo para obtener el comando del Codigo 3D*/
int getCommand(Code3D *code)
{
    return code->command;
}

/**Metodo para saber si un parametro de un Codigo 3D es Integer*/
bool isInt(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_INT;
    if (param == 2)
        return code->param2->type == CODE_INT;
    if (param == 3)
        return code->param3->type == CODE_INT;
	return 0;
}

/**Metodo para saber si un parametro de un Codigo 3D es Float*/
bool isFloat(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_FLOAT;
    if (param == 2)
        return code->param2->type == CODE_FLOAT;
    if (param == 3)
        return code->param3->type == CODE_FLOAT;
    return 0;
}

/**Metodo para saber si un parametro de un Codigo 3D es Booleano*/
bool isBool(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_BOOL;
    if (param == 2)
        return code->param2->type == CODE_BOOL;
    if (param == 3)
        return code->param3->type == CODE_BOOL;
    return 0;
}

/**Metodo para saber si un parametro de un Codigo 3D es un Label*/
bool isLabel(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_LABEL;
    if (param == 2)
        return code->param2->type == CODE_LABEL;
    if (param == 3)
        return code->param3->type == CODE_LABEL;
    return 0;
}

/**Metodo para saber si un parametro de un Codigo 3D es un Attribute*/
bool isAttribute(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_ATTRI;
    if (param == 2)
        return code->param2->type == CODE_ATTRI;
    if (param == 3)
        return code->param3->type == CODE_ATTRI;
    return 0;
}

/**Metodo para saber si un parametro de un Codigo 3D es Null*/
bool isNull(Code3D *code, int param)
{
    if (param == 1)
        return code->param1->type == CODE_NULL;
    if (param == 2)
        return code->param2->type == CODE_NULL;
    if (param == 3)
        return code->param3->type == CODE_NULL;
    return 1;
}

/**Metodo para obtener el parametro Label de un Codigo 3D*/
char* getLabel(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.label;
    if (param == 2)
        return code->param2->val.label;
    if (param == 3)
        return code->param3->val.label;
	return "";
}

/**Metodo para obtener el parametro Attribute de un Codigo 3D*/
Attribute* getAttribute(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.attri;
    if (param == 2)
        return code->param2->val.attri;
    if (param == 3)
        return code->param3->val.attri;
	return NULL;
}

/**Metodo para obtener el parametro Integer de un Codigo 3D*/
int getInt(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.intAttri;
    if (param == 2)
        return code->param2->val.intAttri;
    if (param == 3)
        return code->param3->val.intAttri;
	return 0;
}

/**Metodo para obtener el parametro Float de un Codigo 3D*/
float getFloat(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.floatAttri;
    if (param == 2)
        return code->param2->val.floatAttri;
    if (param == 3)
        return code->param3->val.floatAttri;
	return 0.0;
}

/**Metodo para obtener el parametro Booleano de un Codigo 3D*/
bool getBool(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.boolAttri;
    if (param == 2)
        return code->param2->val.boolAttri;
    if (param == 3)
        return code->param3->val.boolAttri;
    return 0;
}

/**Metodo para setear el parametro con un Bool de un Codigo 3D*/
void setBool(Code3D *code, int param, bool boolAttri)
{
    if (param == 1)
    {
        code->param1->type = CODE_BOOL;
        code->param1->val.boolAttri = boolAttri;
    }
    else if (param == 2)
    {
        code->param2->type = CODE_BOOL;
        code->param2->val.boolAttri = boolAttri;
    }
    else if (param == 3)
    {
        code->param3->type = CODE_BOOL;
        code->param3->val.boolAttri = boolAttri;
    }
}

/**Metodo para setear el parametro con un Float de un Codigo 3D*/
void setFloat(Code3D *code, int param, float floatAttri)
{
    if (param == 1)
    {
        code->param1->type = CODE_FLOAT;
        code->param1->val.floatAttri = floatAttri;
    }
    else if (param == 2)
    {
        code->param2->type = CODE_FLOAT;
        code->param2->val.floatAttri = floatAttri;
    }
    else if (param == 3)
    {
        code->param3->type = CODE_FLOAT;
        code->param3->val.floatAttri = floatAttri;
    }
}

/**Metodo para setear el parametro con un Integer de un Codigo 3D*/
void setInt(Code3D *code, int param, int intAttri)
{
    if (param == 1)
    {
        code->param1->type = CODE_INT;
        code->param1->val.intAttri = intAttri;
    }
    else if (param == 2)
    {
        code->param2->type = CODE_INT;
        code->param2->val.intAttri = intAttri;
    }
    else if (param == 3)
    {
        code->param3->type = CODE_INT;
        code->param3->val.intAttri = intAttri;
    }
}

/**Metodo para setear el parametro con un Label de un Codigo 3D*/
void setLabel(Code3D *code, int param, char *label)
{
    if (param == 1)
	{
        code->param1->type = CODE_LABEL;
        code->param1->val.label = strdup(label);
    }
	if (param == 2)
	{
        code->param2->type = CODE_LABEL;
        code->param2->val.label = strdup(label);
    }
	if (param == 3)
	{
        code->param3->type = CODE_LABEL;
        code->param3->val.label = strdup(label);
	}
}

/**Metodo para setear el parametro con un Attribute de un Codigo 3D*/
void setAttribute(Code3D *code, int param, Attribute *attri)
{
    if (param == 1)
    {
        code->param1->type = CODE_ATTRI;
        code->param1->val.attri = attri;
    }
    if (param == 2)
    {
        code->param2->type = CODE_ATTRI;
        code->param2->val.attri = attri;
    }
    if (param == 3)
    {
        code->param3->type = CODE_ATTRI;
        code->param3->val.attri = attri;
    }
}

/**Metodo para setear el parametro en Null de un Codigo 3D*/
void setNull(Code3D *code, int param) {
    if (param == 1)
        code->param1->type = CODE_NULL;
	if (param == 2)
        code->param2->type = CODE_NULL;
    if (param == 3)
        code->param3->type = CODE_NULL;
}

/**Metodo para setear los parametros de un Label en el Codigo 3D*/
void setCodeLabel(Code3D *code, char *label)
{
    setLabel(code, 1, label);
    setNull(code, 2);
    setNull(code, 3);
}

/**Metodo para setear los parametros de un Label Condicional en el Codigo 3D*/
void setCodeLabelCond(Code3D *code, Attribute *attri1, char *labelJumpTo)
{
    setAttribute(code, 1, attri1);
    setLabel(code, 2, labelJumpTo);
    setNull(code, 3);
}

/**Metodo para setear los parametros de un Comando con 3 Attribute en el Codigo 3D*/
void setCode3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes)
{
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attri2);
    setAttribute(code, 3, attriRes);
}

/**Metodo para setear los parametros de un Comando con 2 Attribute en el Codigo 3D*/
void setCode2D(Code3D *code, Attribute *attri1, Attribute *attriRes)
{
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attriRes);
    setNull(code, 3);
}

/**Metodo para setear los parametros de un Comando con 1 Attribute en el Codigo 3D*/
void setCode1D(Code3D *code, Attribute *attri1)
{
    setAttribute(code, 1, attri1);
    setNull(code, 2);
    setNull(code, 3);
}

/**Muestra un parametro de un Codigo 3D*/
void showCode(Code3D *code, int param)
{
    if (isNull(code, param))
        printf("    -     |  ");
    else
    {
        if (isInt(code, param))
            printf(" %i   |    ", getInt(code, param));
        if (isFloat(code, param))
            printf("%f   |  ", getFloat(code, param));
        if (isBool(code, param))
            printf("%s   |  ", getBool(code, param)? "true" : "false");
        if (isLabel(code, param))
            printf("%s   |  ", getLabel(code, param));
        if (isAttribute(code, param))
            printf("%s   |  ", getID(getAttribute(code,param)));
    }
}

//Muestro el codigo intermedio de manera correcta.
void toString3DC(Code3D *code)
{
    printf("   %s   |   ", (char*)get_operation_by_id(getCommand(code)));
	if (isNull(code, 3))
	{
		if (isNull(code, 2))
		{
			showCode(code,1);
			showCode(code,2);
		}
		else
		{
			showCode(code,2);
			showCode(code,1);
		}
		showCode(code,3);
	}
	else
	{
		showCode(code,3);
		showCode(code,1);
		showCode(code,2);
	}
    printf("\n------------------------------------------------------------\n");
}
