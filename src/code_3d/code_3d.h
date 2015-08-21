/*
* Struct for code three directions and respective functions.
*
* A code have:
*   command :   id of command
*   param1  :   first param command
*   param2  :   second param command
*   param3  :   third param command
*/

#ifndef CODE_3D_H
#define CODE_3D_H

#include "../SymbolsTable/Attribute.h"
#include <stdbool.h>

typedef union {
    int         intAttri;
    float       floatAttri;
    bool        boolAttri;
    Attribute   *attri;
    char        *label;
} Value;

typedef struct {
    int   type; // -1 : null, 0 : Attribute, 1 : label, 2 : Integer, 3 : Float, 4 : Bool
    Value val;
} Param;

typedef struct {
    int command;
    Param *param1;
    Param *param2;
    Param *param3;
} Code3D;


/* 3d code constructor. */
Code3D* newCode(int comm);

/* Functions for management 3d code */
int getCommand(Code3D *code);
bool isInt(Code3D *code, int param);
bool isFloat(Code3D *code, int param);
bool isBool(Code3D *code, int param);
bool isLabel(Code3D *code, int param);
bool isAttribute(Code3D *code, int param);
bool isNull(Code3D *code, int param);
char* getLabel(Code3D *code, int param);
Attribute* getAttribute(Code3D *code, int param);
int getInt(Code3D *code, int param);
float getFloat(Code3D *code, int param);
bool getBool(Code3D *code, int param);

/**Funciones de Escritura de un Codigo*/

void setBool(Code3D *code, int param, bool boolAttri);
void setFloat(Code3D *code, int param, float floatAttri);
void setInt(Code3D *code, int param, int intAttri);
void setLabel(Code3D *code, int param, char *label);
void setAttribute(Code3D *code, int param, Attribute *attri);
void setNull(Code3D *code, int param);

/** Funciones de Escritura de un Codigo Concreto*/

void setCodeLabel(Code3D *code, char *label);
void setCodeLabelCond(Code3D *code, Attribute *attri1, char *labelJumpTo);
void setCode3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes);
void setCode2D(Code3D *code, Attribute *attri1, Attribute *attriRes);
void setCode1D(Code3D *code, Attribute *attri1);

void toString3DC(Code3D *code);

#endif