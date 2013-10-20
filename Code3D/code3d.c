/**********************************************************************
*Implementacion Codigo de 3 Direcciones                               *
**********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "code3d.h"

Code3D* newCode(int comm) {
    Code3D *new = (Code3D*) malloc(sizeof(Code3D));
    Param *param1 = (Param*) malloc(sizeof(Param));
    Param *param2 = (Param*) malloc(sizeof(Param));
    Param *param3 = (Param*) malloc(sizeof(Param));
    param1->type = CodeNULL;
    param2->type = CodeNULL;
    param3->type = CodeNULL;
    new->param1 = param1;
    new->param2 = param2;
    new->param3 = param3;
    new->command = comm;
    return new;
}

int getCommand(Code3D *code) {
    return code->command;    
}

bool isInt(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeINT;
    } else if (param == 2) {
        return code->param2->type == CodeINT;
    } else if (param == 3) {
        return code->param3->type == CodeINT;
    }  
}

bool isFloat(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeFLOAT;
    } else if (param == 2) {
        return code->param2->type == CodeFLOAT;
    } else if (param == 3) {
        return code->param3->type == CodeFLOAT;
    }      
}

bool isBool(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeBOOL;
    } else if (param == 2) {
        return code->param2->type == CodeBOOL;
    } else if (param == 3) {
        return code->param3->type == CodeBOOL;
    }
}

bool isLabel(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeLABEL;
    } else if (param == 2) {
        return code->param2->type == CodeLABEL;
    } else if (param == 3) {
        return code->param3->type == CodeLABEL;
    }
}

bool isAttribute(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeATTRI;
    } else if (param == 2) {
        return code->param2->type == CodeATTRI;
    } else if (param == 3) {
        return code->param3->type == CodeATTRI;
    }    
}

bool isVariable(Code3D *code, int param){
    if (param == 1) {
        return code->param1->type == CodeVARIABLE;
    } else if (param == 2) {
        return code->param2->type == CodeVARIABLE;
    } else if (param == 3) {
        return code->param3->type == CodeVARIABLE;
    }   
}

bool isNull(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->type == CodeNULL;
    } else if (param == 2) {
        return code->param2->type == CodeNULL;
    } else if (param == 3) {
        return code->param3->type == CodeNULL;
    }    
}

char* getLabel(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->val->label;
    } else if (param == 2) {
        return code->param2->val->label;
    } else if (param == 3) {
        return code->param3->val->label;
    }    
}

Attribute* getAttribute(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->val->attri;
    } else if (param == 2) {
        return code->param2->val->attri;
    } else if (param == 3) {
        return code->param3->val->attri;
    }
}

StVariable* getVariable(Code3D *code, int param){
    if (param == 1) {
        return code->param1->val->variable;
    } else if (param == 2) {
        return code->param2->val->variable;
    } else if (param == 3) {
        return code->param3->val->variable;
    }
}

int getInt(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->val->intAttri;
    } else if (param == 2) {
        return code->param2->val->intAttri;
    } else if (param == 3) {
        return code->param3->val->intAttri;
    }    
}

float getFloat(Code3D *code, int param) {
    if (param == 1) {
        return code->param1->val->floatAttri;
    } else if (param == 2) {
        return code->param2->val->floatAttri;
    } else if (param == 3) {
        return code->param3->val->floatAttri;
    }    
}

int getBool(Code3D *code, int param) {
    if (param == 1) {
        if (code->param1->val->boolAttri) {
            return 1;
        }
    } else if (param == 2) {
        if (code->param2->val->boolAttri) {
            return 1;
        }
    } else if (param == 3) {
        if (code->param3->val->boolAttri) {
            return 1;
        }
    }
    return 0;
}


void setBool(Code3D *code, int param, bool boolAttri) {
    if (param == 1) {
        code->param1->type = CodeBOOL;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->boolAttri = boolAttri;
    } else if (param == 2) {
        code->param2->type = CodeBOOL;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->boolAttri = boolAttri;
    } else if (param == 3) {
        code->param3->type = CodeBOOL;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->boolAttri = boolAttri;
    }
}

void setFloat(Code3D *code, int param, float floatAttri) {
    if (param == 1) {
        code->param1->type = CodeFLOAT;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->floatAttri = floatAttri;
    } else if (param == 2) {
        code->param2->type = CodeFLOAT;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->floatAttri = floatAttri;
    } else if (param == 3) {
        code->param3->type = CodeFLOAT;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->floatAttri = floatAttri;
    }    
}

void setInt(Code3D *code, int param, int intAttri) {
    if (param == 1) {
        code->param1->type = CodeINT;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->intAttri = intAttri;
    } else if (param == 2) {
        code->param2->type = CodeINT;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->intAttri = intAttri;
    } else if (param == 3) {
        code->param3->type = CodeINT;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->intAttri = intAttri;
    }
}


void setLabel(Code3D *code, int param, char *label) {
    if (param == 1) {
        code->param1->type = CodeLABEL;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->label = malloc(strlen(label) + 1);
        strcpy(code->param1->val->label, label);
    } else if (param == 2) {
        code->param2->type = CodeLABEL;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->label = malloc(strlen(label) + 1);
        strcpy(code->param2->val->label, label);
    } else if (param == 3) {
        code->param3->type = CodeLABEL;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->label = malloc(strlen(label) + 1);
        strcpy(code->param3->val->label, label);
    }    
}

void setAttribute(Code3D *code, int param, Attribute *attri) {
    if (param == 1) {
        code->param1->type = CodeATTRI;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->attri = attri;
    } else if (param == 2) {
        code->param2->type = CodeATTRI;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->attri = attri;
    } else if (param == 3) {
        code->param3->type = CodeATTRI;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->attri = attri;
    }    
}

void setVariable(Code3D *code, int param, StVariable *variable){
	    if (param == 1) {
        code->param1->type = CodeVARIABLE;
        code->param1->val = (Value*) malloc(sizeof(Value));
        code->param1->val->variable = variable;
    } else if (param == 2) {
        code->param2->type = CodeVARIABLE;
        code->param2->val = (Value*) malloc(sizeof(Value));
        code->param2->val->variable = variable;
    } else if (param == 3) {
        code->param3->type = CodeVARIABLE;
        code->param3->val = (Value*) malloc(sizeof(Value));
        code->param3->val->variable = variable;
    } 
}

void setNull(Code3D *code, int param) {
    if (param == 1) {
        code->param1->type = CodeNULL;
    } else if (param == 2) {
        code->param2->type = CodeNULL;
    } else if (param == 3) {
        code->param3->type = CodeNULL;
    } 
}

void setCodeLabel(Code3D *code, char *label){
    setLabel(code, 1, label);
    setNull(code, 2);
    setNull(code, 3);
}

void setCodeLabelCond(Code3D *code, Attribute *attri1, char *label){
    setAttribute(code, 1, attri1);
    setLabel(code, 2, label);
    setNull(code, 3);
}

void setCode3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes){
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attri2);
    setAttribute(code, 3, attriRes);
}

void setCode2D(Code3D *code, Attribute *attri1, Attribute *attriRes){
    setAttribute(code, 1, attri1);
    setAttribute(code, 2, attriRes);
    setNull(code, 3);
}

void setCode1D(Code3D *code, Attribute *attri1){
    setAttribute(code, 1, attri1);
    setNull(code, 2);
    setNull(code, 3);
}

void toString3DC(Code3D *code) {
    // Ver si funciona
    printf("   %s   |   ", getCodeByID(getCommand(code)));
  //  printf("%s   |    ", getTypeByID(code->param1->type));
    if (isNull(code, 1)){
        printf("    -     |  ");
    }
    else {
        if (isInt(code, 1)){
            printf("(I)");
            printf("%i   |    ", getInt(code, 1));
        }
        if (isFloat(code, 1)){
            printf("(F)");
            printf("%f |  ", getFloat(code, 1));
        }
        if (isBool(code, 1)){
            printf("(B)");
            printf("%s |  ", getBool(code, 1)? "true" : "false");
        }
        if (isLabel(code, 1)){
            printf("(L)");
            printf("%s |  ", getLabel(code, 1));
        }
        if (isAttribute(code, 1)){
            printf("(A)");
            printf("%s |  ", getType(getAttribute(code, 1)->type));
        }
    }
    if (isNull(code, 2)){
        printf("    -     |  ");
    }
    else {
        if (isInt(code, 2)){
            printf("(I)");
            printf("%i   |    ", getInt(code, 2));
        }
        if (isFloat(code, 2)){
            printf("(F)");
            printf("%f |  ", getFloat(code, 2));
        }
        if (isBool(code, 2)){
            printf("(B)");
            printf("%s |  ", getBool(code, 2)? "true" : "false");
        }
        if (isLabel(code, 2)){
            printf("(L)");
            printf("%s |  ", getLabel(code, 2));
        }
        if (isAttribute(code, 2)){
            printf("(A)");
            printf("%s |  ", getType(getAttribute(code, 2)->type));
        }
    }
    if (isNull(code, 3)){
        printf("    -     |  ");
    }
    else {
        if (isInt(code, 3)){
            printf("(I)");
            printf("%i   |    ", getInt(code, 3));
        }
        if (isFloat(code, 3)){
            printf("(F)");
            printf("%f |  ", getFloat(code, 3));
        }
        if (isBool(code, 3)){
            printf("(B)");
            printf("%s |  ", getBool(code, 3)? "true" : "false");
        }
        if (isLabel(code, 3)){
            printf("(L)");
            printf("%s |  ", getLabel(code, 3));
        }
        if (isAttribute(code, 3)){
            printf("(A)");
            printf("%s |  ", getType(getAttribute(code, 3)->type));
        }
    }
    printf("\n------------------------------------------------------------\n");
}


