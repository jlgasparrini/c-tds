/************************************************************************
*Define la estructura de los codigos de 3 direcciones y funciones      *
*asociadas                                                              *
*                                                                       *
*Una codigo va a tener :                                              *
* comando   	 :   identificador del comando 		                    *
* parametro1     :   primer parametro del comando                       *
* parametro2     :   segundo parametro del comando                      *
* parametro3     :   tercer parametro del comando                       *
************************************************************************/

#ifndef CODE3D_H
#define CODE3D_H

#include "../SymbolsTable/Attribute.h"
#include <stdbool.h>


#define CodeNULL    -1
#define CodeATTRI    0
#define CodeLABEL    1
#define CodeINT      2
#define CodeFLOAT    3
#define CodeBOOL     4
#define CodeVARIABLE 5

typedef union {
    int         intAttri;
    float       floatAttri;
    bool        boolAttri;
    Attribute   *attri;
    char        *label;
	StVariable	*variable;
} Value;

typedef struct {
    int   type; // -1 : null, 0 : Attribute, 1 : label, 2 : Integer, 3 : Float, 4 : Bool, 5: StVariable
    Value val; 
} Param;

typedef struct {
    int command;
    Param *param1;
    Param *param2;
    Param *param3;
} Code3D;


/**Constructor de un Codigo*/

Code3D* newCode(int comm);

/**Funciones de Acceso a un Codigo*/

int getCommand(Code3D *code);
bool isInt(Code3D *code, int param);
bool isFloat(Code3D *code, int param);
bool isBool(Code3D *code, int param);
bool isLabel(Code3D *code, int param);
bool isAttribute(Code3D *code, int param);
bool isVariable(Code3D *code, int param);
bool isNull(Code3D *code, int param);
char* getLabel(Code3D *code, int param);
Attribute* getAttribute(Code3D *code, int param);
StVariable* getVariable(Code3D *code, int param);
int getInt(Code3D *code, int param);
float getFloat(Code3D *code, int param);
int getBool(Code3D *code, int param);

/**Funciones de Escritura de un Codigo*/

void setBool(Code3D *code, int param, bool boolAttri);
void setFloat(Code3D *code, int param, float floatAttri);
void setInt(Code3D *code, int param, int intAttri);
void setLabel(Code3D *code, int param, char *label);
void setAttribute(Code3D *code, int param, Attribute *attri);
void setVariable(Code3D *code, int param, StVariable *variable);
void setNull(Code3D *code, int param);

/** Funciones de Escritura de un Codigo Concreto*/

void setCodeLabel(Code3D *code, char *label);
void setCodeLabelCond(Code3D *code, Attribute *attri1, char *labelJumpTo);
void setCode3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes);
void setCode2D(Code3D *code, Attribute *attri1, Attribute *attriRes);
void setCode1D(Code3D *code, Attribute *attri1);

void toString3DC(Code3D *code);

#endif
