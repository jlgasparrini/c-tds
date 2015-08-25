/*
 * Code 3d implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "code_3d.h"
#include "operations_code.h"

#define CODE_NULL    -1
#define CODE_ATTRI    0
#define CODE_LABEL    1
#define CODE_INT      2
#define CODE_FLOAT    3
#define CODE_BOOL     4

/* Code 3d constructor. */
Code3D* new_ode(int comm)
{
  Code3D *code = (Code3D*) malloc(sizeof(Code3D));
  code->param1 = (Param*) malloc(sizeof(Param));
  code->param2 = (Param*) malloc(sizeof(Param));
  code->param3 = (Param*) malloc(sizeof(Param));
  code->param1->type = CODE_NULL;
  code->param2->type = CODE_NULL;
  code->param3->type = CODE_NULL;
  code->command = comm;
  return code;
}

/**Metodo para obtener el comando del Codigo 3D*/
int get_command(Code3D *code)
{
  return code->command;
}

/**Metodo para saber si un parametro de un Codigo 3D es Integer*/
bool is_int(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_INT;
    case 2: return code->param2->type == CODE_INT;
    case 3: return code->param3->type == CODE_INT;
    default: return 0;
  }
}

/**Metodo para saber si un parametro de un Codigo 3D es Float*/
bool is_float(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_FLOAT;
    case 2: return code->param2->type == CODE_FLOAT;
    case 3: return code->param3->type == CODE_FLOAT;
    default: return 0;
  }
}

/**Metodo para saber si un parametro de un Codigo 3D es Booleano*/
bool is_bool(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_BOOL;
    case 2: return code->param2->type == CODE_BOOL;
    case 3: return code->param3->type == CODE_BOOL;
    default: return 0;
  }
}

/**Metodo para saber si un parametro de un Codigo 3D es un Label*/
bool is_label(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_LABEL;
    case 2: return code->param2->type == CODE_LABEL;
    case 3: return code->param3->type == CODE_LABEL;
    default: return 0;
  }
}

/**Metodo para saber si un parametro de un Codigo 3D es un Attribute*/
bool is_attribute(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_ATTRI;
    case 2: return code->param2->type == CODE_ATTRI;
    case 3: return code->param3->type == CODE_ATTRI;
    default: return 0;
  } 
}

/**Metodo para saber si un parametro de un Codigo 3D es Null*/
bool is_null(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->type == CODE_NULL;
    case 2: return code->param2->type == CODE_NULL;
    case 3: return code->param3->type == CODE_NULL;
    default: return 1;
  } 
}

/**Metodo para obtener el parametro Label de un Codigo 3D*/
char* get_label(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->val.label;
    case 2: return code->param2->val.label;
    case 3: return code->param3->val.label;
    default: return "";
  } 
}

/**Metodo para obtener el parametro Attribute de un Codigo 3D*/
Attribute* get_attribute(Code3D *code, int param)
{
  switch (param)
  {
    case 1: return code->param1->val.attri;
    case 2: return code->param2->val.attri;
    case 3: return code->param3->val.attri;
    default: return NULL;
  }  
}

/**Metodo para obtener el parametro Integer de un Codigo 3D*/
int get_int(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.intAttri;
    case 2: return code->param2->val.intAttri;
    case 3: return code->param3->val.intAttri;
    default: return 0;
  }   
}

/**Metodo para obtener el parametro Float de un Codigo 3D*/
float get_float(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.floatAttri;
    case 2: return code->param2->val.floatAttri;
    case 3: return code->param3->val.floatAttri;
    default: return 0.0;
  }  
}

/**Metodo para obtener el parametro Booleano de un Codigo 3D*/
bool get_bool(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.boolAttri;
    case 2: return code->param2->val.boolAttri;
    case 3: return code->param3->val.boolAttri;
    default: return 0;
  }  
}

/**Metodo para setear el parametro con un Bool de un Codigo 3D*/
void set_bool(Code3D *code, int param, bool boolAttri)
{
  switch (param)
  {
    case 1: code->param1->type = CODE_BOOL;
            code->param1->val.boolAttri = boolAttri;
            break;
    case 2: code->param2->type = CODE_BOOL;
            code->param2->val.boolAttri = boolAttri;
            break;
    case 3: code->param3->type = CODE_BOOL;
            code->param3->val.boolAttri = boolAttri;
            break;
    default: break;
  }
}

/**Metodo para setear el parametro con un Float de un Codigo 3D*/
void set_float(Code3D *code, int param, float floatAttri)
{
  switch (param)
  {
    case 1: code->param1->type = CODE_FLOAT;
            code->param1->val.floatAttri = floatAttri;
            break;
    case 2: code->param2->type = CODE_FLOAT;
            code->param2->val.floatAttri = floatAttri;
            break;
    case 3: code->param3->type = CODE_FLOAT;
            code->param3->val.floatAttri = floatAttri;
            break;
    default: break;
  }
}

/**Metodo para setear el parametro con un Integer de un Codigo 3D*/
void set_int(Code3D *code, int param, int intAttri)
{
  switch (param)
  {
    case 1: code->param1->type = CODE_INT;
            code->param1->val.intAttri = intAttri;
            break;
    case 2: code->param2->type = CODE_INT;
            code->param2->val.intAttri = intAttri;
            break;
    case 3: code->param3->type = CODE_INT;
            code->param3->val.intAttri = intAttri;
            break;
    default: break;
  }
}

/**Metodo para setear el parametro con un Label de un Codigo 3D*/
void set_label(Code3D *code, int param, char *label)
{
  switch (param)
  {
    case 1: code->param1->type = CODE_LABEL;
            code->param1->val.label = strdup(label);
            break;
    case 2: code->param2->type = CODE_LABEL;
            code->param2->val.label = strdup(label);
            break;
    case 3: code->param3->type = CODE_LABEL;
            code->param3->val.label = strdup(label);
            break;
    default: break;
  }
}

/**Metodo para setear el parametro con un Attribute de un Codigo 3D*/
void set_attribute(Code3D *code, int param, Attribute *attri)
{
  switch (param)
  {
    case 1: code->param1->type = CODE_ATTRI;
            code->param1->val.attri = attri;
            break;
    case 2: code->param2->type = CODE_ATTRI;
            code->param2->val.attri = attri;
            break;
    case 3: code->param3->type = CODE_ATTRI;
            code->param3->val.attri = attri;
            break;
    default: break;
  }
}

/**Metodo para setear el parametro en Null de un Codigo 3D*/
void set_null(Code3D *code, int param) {
  switch (param)
  {
    case 1: code->param1->type = CODE_NULL; break;
    case 2: code->param2->type = CODE_NULL; break;
    case 3: code->param3->type = CODE_NULL; break;
    default: break;
  }
}

/**Metodo para setear los parametros de un Label en el Codigo 3D*/
void set_code_label(Code3D *code, char *label)
{
  set_label(code, 1, label);
  set_null(code, 2);
  set_null(code, 3);
}

/**Metodo para setear los parametros de un Label Condicional en el Codigo 3D*/
void set_code_label_cond(Code3D *code, Attribute *attri1, char *labelJumpTo)
{
  set_attribute(code, 1, attri1);
  set_label(code, 2, labelJumpTo);
  set_null(code, 3);
}

/**Metodo para setear los parametros de un Comando con 3 Attribute en el Codigo 3D*/
void set_c3D(Code3D *code, Attribute *attri1, Attribute *attri2, Attribute *attriRes)
{
  set_attribute(code, 1, attri1);
  set_attribute(code, 2, attri2);
  set_attribute(code, 3, attriRes);
}

/**Metodo para setear los parametros de un Comando con 2 Attribute en el Codigo 3D*/
void set_c2D(Code3D *code, Attribute *attri1, Attribute *attriRes)
{
  set_attribute(code, 1, attri1);
  set_attribute(code, 2, attriRes);
  set_null(code, 3);
}

/**Metodo para setear los parametros de un Comando con 1 Attribute en el Codigo 3D*/
void set_c1D(Code3D *code, Attribute *attri1)
{
  set_attribute(code, 1, attri1);
  set_null(code, 2);
  set_null(code, 3);
}

/**Muestra un parametro de un Codigo 3D*/
void show_code(Code3D *code, int param)
{
  if (is_null(code, param))
    printf("    -     |  ");
  else
  {
    if (is_int(code, param))
      printf(" %i   |    ", get_int(code, param));
    if (is_float(code, param))
      printf("%f   |  ", get_float(code, param));
    if (is_bool(code, param))
      printf("%s   |  ", get_bool(code, param)? "true" : "false");
    if (is_label(code, param))
      printf("%s   |  ", get_label(code, param));
    if (is_attribute(code, param))
      printf("%s   |  ", get_id(get_attribute(code,param)));
  }
}

//Muestro el codigo intermedio de manera correcta.
void to_string_c3D(Code3D *code)
{
  printf("   %s   |   ", (char*) get_operation_by_id(get_command(code)));
  if (is_null(code, 3))
  {
    if (is_null(code, 2))
    {
      show_code(code,1);
      show_code(code,2);
    }
    else
    {
      show_code(code,2);
      show_code(code,1);
    }
    show_code(code,3);
  }
  else
  {
    show_code(code,3);
    show_code(code,1);
    show_code(code,2);
  }
  printf("\n------------------------------------------------------------\n");
}
