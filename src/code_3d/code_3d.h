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
Code3D* new_ode(int comm);

/* Functions for management 3d code */
int get_command(Code3D *code);
bool is_int(Code3D *code, int param);
bool is_float(Code3D *code, int param);
bool is_bool(Code3D *code, int param);
bool is_label(Code3D *code, int param);
bool is_attribute(Code3D *code, int param);
bool is_null(Code3D *code, int param);
char* get_label(Code3D *code, int param);
Attribute* get_attribute(Code3D *code, int param);
int get_int(Code3D *code, int param);
float get_float(Code3D *code, int param);
bool get_bool(Code3D *code, int param);

/**Funciones de Escritura de un Codigo*/

void set_bool(Code3D *code, int param, bool boolAttri);
void set_float(Code3D *code, int param, float floatAttri);
void set_int(Code3D *code, int param, int intAttri);
void set_label(Code3D *code, int param, char *label);
void set_attribute(Code3D *code, int param, Attribute *attri);
void set_null(Code3D *code, int param);

/** Funciones de Escritura de un Codigo Concreto*/

void set_code_label(Code3D *code, char *label);
void set_code_label_cond(Code3D *code, Attribute *attri1, char *labelJumpTo);
void set_c3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes);
void set_c2D(Code3D *code, Attribute *attri1, Attribute *attriRes);
void set_c1D(Code3D *code, Attribute *attri1);

void to_string_c3D(Code3D *code);

#endif
