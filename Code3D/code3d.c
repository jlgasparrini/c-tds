/**********************************************************************
 *Implementacion Codigo de 3 Direcciones                               *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "code3d.h"

Code3D* newCode(int comm) 
{
    Code3D *new = (Code3D*) malloc(sizeof(Code3D));
    (*new).param1 = (Param*) malloc(sizeof(Param));
    (*new).param2 = (Param*) malloc(sizeof(Param));
    (*new).param3 = (Param*) malloc(sizeof(Param));
	(*new).param1->type = CodeNULL;
	(*new).param2->type = CodeNULL;
	(*new).param3->type = CodeNULL;
    (*new).command = comm;
    return new;
}

int getCommand(Code3D *code) 
{
    return code->command;    
}

bool isInt(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeINT;
    }
    else if (param == 2) 
    {
        return code->param2->type == CodeINT;
    }
    else if (param == 3) 
    {
        return code->param3->type == CodeINT;
    }  
    return 0;
}

bool isFloat(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeFLOAT;
    }
    else if (param == 2) 
    {
        return code->param2->type == CodeFLOAT;
    } 
    else if (param == 3) 
    {
        return code->param3->type == CodeFLOAT;
    }      
    return 0;
}

bool isBool(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeBOOL;
    }
    else if (param == 2) 
    {
        return code->param2->type == CodeBOOL;
    }
    else if (param == 3) 
    {
        return code->param3->type == CodeBOOL;
    }
    return 0;
}

bool isLabel(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeLABEL;
    }
    else if (param == 2) 
    {
        return code->param2->type == CodeLABEL;
    } 
    else if (param == 3) 
    {
        return code->param3->type == CodeLABEL;
    }
    return 0;
}

bool isAttribute(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeATTRI;
    }
    else if (param == 2) 
    {
        return code->param2->type == CodeATTRI;
    }
    else if (param == 3) 
    {
        return code->param3->type == CodeATTRI;
    }    
    return 0;
}

bool isVariable(Code3D *code, int param)
{
    if (param == 1) 
    {
        return code->param1->type == CodeVARIABLE;
    } 
    else if (param == 2) 
    {
        return code->param2->type == CodeVARIABLE;
    } 
    else if (param == 3) 
    {
        return code->param3->type == CodeVARIABLE;
    }   
    return 0;
}

bool isNull(Code3D *code, int param) 
{
    if (param == 1) 
    {
        return code->param1->type == CodeNULL;
    } 
    else if (param == 2) 
    {
        return code->param2->type == CodeNULL;
    } 
    else if (param == 3) 
    {
        return code->param3->type == CodeNULL;
    }
    return 1;
}

char* getLabel(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.label;
    if (param == 2)
        return code->param2->val.label;
    if (param == 3)
        return code->param3->val.label;
	return "";
}

Attribute* getAttribute(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.attri;
    if (param == 2)
        return code->param2->val.attri;
    if (param == 3)
        return code->param3->val.attri;
	return NULL;
}

StVariable* getVariable(Code3D *code, int param){
    if (param == 1)
        return code->param1->val.variable;
    if (param == 2)
        return code->param2->val.variable;
    if (param == 3)
        return code->param3->val.variable;
	return NULL;
}

int getInt(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.intAttri;
    if (param == 2)
        return code->param2->val.intAttri;
    if (param == 3)
        return code->param3->val.intAttri;
	return 0;
}

float getFloat(Code3D *code, int param) {
    if (param == 1)
        return code->param1->val.floatAttri;
    if (param == 2)
        return code->param2->val.floatAttri;
    if (param == 3)
        return code->param3->val.floatAttri;
	return 0.0;
}

int getBool(Code3D *code, int param) {
    if (param == 1)
        if (code->param1->val.boolAttri)
            return 1;
    if (param == 2)
        if (code->param2->val.boolAttri)
            return 1;
    if (param == 3)
        if (code->param3->val.boolAttri)
            return 1;
    return 0;
}


void setBool(Code3D *code, int param, bool boolAttri) 
{
    if (param == 1) 
    {
        code->param1->type = CodeBOOL;
        code->param1->val.boolAttri = boolAttri;
    } 
    else if (param == 2) 
    {
        code->param2->type = CodeBOOL;
        code->param2->val.boolAttri = boolAttri;
    }
    else if (param == 3) 
    {
        code->param3->type = CodeBOOL;
        code->param3->val.boolAttri = boolAttri;
    }
}

void setFloat(Code3D *code, int param, float floatAttri) 
{
    if (param == 1) 
    {
        code->param1->type = CodeFLOAT;
        code->param1->val.floatAttri = floatAttri;
    } 
    else if (param == 2) 
    {
        code->param2->type = CodeFLOAT;
        code->param2->val.floatAttri = floatAttri;
    } 
    else if (param == 3) 
    {
        code->param3->type = CodeFLOAT;
        code->param3->val.floatAttri = floatAttri;
    }    
}

void setInt(Code3D *code, int param, int intAttri) 
{
    if (param == 1) 
    {
        code->param1->type = CodeINT;
        code->param1->val.intAttri = intAttri;
    }
    else if (param == 2) 
    {
        code->param2->type = CodeINT;
        code->param2->val.intAttri = intAttri;
    } 
    else if (param == 3) 
    {
        code->param3->type = CodeINT;
        code->param3->val.intAttri = intAttri;
    }
}


void setLabel(Code3D *code, int param, char *label) 
{
    if (param == 1)
	{
        code->param1->type = CodeLABEL;
        code->param1->val.label = strdup(label);
    } 
	if (param == 2) 
	{
        code->param2->type = CodeLABEL;
        code->param2->val.label = strdup(label);
    }
	if (param == 3) 
	{
        code->param3->type = CodeLABEL;
        code->param3->val.label = strdup(label);
	}    
}

void setAttribute(Code3D *code, int param, Attribute *attri) 
{
    if (param == 1) 
    {
        code->param1->type = CodeATTRI;
        code->param1->val.attri = (Attribute*) malloc(sizeof(Attribute));
        code->param1->val.attri = attri;
    } 
    else if (param == 2) 
    {
        code->param2->type = CodeATTRI;
        code->param2->val.attri = (Attribute*) malloc(sizeof(Attribute));
        code->param2->val.attri = attri;
    }
    else if (param == 3) 
    {
        code->param3->type = CodeATTRI;
        code->param3->val.attri = (Attribute*) malloc(sizeof(Attribute));
        code->param3->val.attri = attri;
    }    
}

void setVariable(Code3D *code, int param, StVariable *variable){
	if (param == 1) {
        code->param1->type = CodeVARIABLE;
        code->param1->val.variable = (StVariable*) malloc(sizeof(StVariable));
        code->param1->val.variable = variable;
    } 
    else if (param == 2) 
    {
        code->param2->type = CodeVARIABLE;
        code->param2->val.variable = (StVariable*) malloc(sizeof(StVariable));
        code->param2->val.variable = variable;
    } 
    else if (param == 3) 
    {
        code->param3->type = CodeVARIABLE;
        code->param3->val.variable = (StVariable*) malloc(sizeof(StVariable));
        code->param3->val.variable = variable;
    } 
}

void setNull(Code3D *code, int param) {
    if (param == 1) 
        code->param1->type = CodeNULL;
	if (param == 2)
        code->param2->type = CodeNULL;
    if (param == 3)
        code->param3->type = CodeNULL;
}

void setCodeLabel(Code3D *code, char *label)
{
    setLabel(code, 1, label);
    setNull(code, 2);
    setNull(code, 3);
}

void setCodeLabelCond(Code3D *code, Attribute *attri1, char *label, char *jumpTo)
{
    setAttribute(code, 1, attri1);
    setLabel(code, 2, label);
    setLabel(code, 3, jumpTo);
}

void setCode3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes)
{
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attri2);
    setAttribute(code, 3, attriRes);
}

void setCode2D(Code3D *code, Attribute *attri1, Attribute *attriRes)
{
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attriRes);
    setNull(code, 3);
}

void setCode1D(Code3D *code, Attribute *attri1)
{
    setAttribute(code, 1, attri1);
    setNull(code, 2);
    setNull(code, 3);
}

void showCode(Code3D *code, int param)
{
    if (isNull(code, param))
        printf("    -     |  ");
    else 
    {
        if (isInt(code, param))
            printf("%i   |    ", getInt(code, param));
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

void toString3DC(Code3D *code) 
{
    printf("   %s   |   ", (char*)getCodeByID(getCommand(code)));
	/* Shows the Code in the right way */
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
