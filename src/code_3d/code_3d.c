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
Code3D* newCode(int comm)
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
int getCommand(Code3D *code)
{
  return code->command;
}

/**Metodo para saber si un parametro de un Codigo 3D es Integer*/
bool isInt(Code3D *code, int param)
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
bool isFloat(Code3D *code, int param)
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
bool isBool(Code3D *code, int param)
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
bool isLabel(Code3D *code, int param)
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
bool isAttribute(Code3D *code, int param)
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
bool isNull(Code3D *code, int param)
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
char* getLabel(Code3D *code, int param)
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
Attribute* getAttribute(Code3D *code, int param)
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
int getInt(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.intAttri;
    case 2: return code->param2->val.intAttri;
    case 3: return code->param3->val.intAttri;
    default: return 0;
  }   
}

/**Metodo para obtener el parametro Float de un Codigo 3D*/
float getFloat(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.floatAttri;
    case 2: return code->param2->val.floatAttri;
    case 3: return code->param3->val.floatAttri;
    default: return 0.0;
  }  
}

/**Metodo para obtener el parametro Booleano de un Codigo 3D*/
bool getBool(Code3D *code, int param) {
  switch (param)
  {
    case 1: return code->param1->val.boolAttri;
    case 2: return code->param2->val.boolAttri;
    case 3: return code->param3->val.boolAttri;
    default: return 0;
  }  
}

/**Metodo para setear el parametro con un Bool de un Codigo 3D*/
void setBool(Code3D *code, int param, bool boolAttri)
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
void setFloat(Code3D *code, int param, float floatAttri)
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
void setInt(Code3D *code, int param, int intAttri)
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
void setLabel(Code3D *code, int param, char *label)
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
void setAttribute(Code3D *code, int param, Attribute *attri)
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
void setNull(Code3D *code, int param) {
  switch (param)
  {
    case 1: code->param1->type = CODE_NULL; break;
    case 2: code->param2->type = CODE_NULL; break;
    case 3: code->param3->type = CODE_NULL; break;
    default: break;
  }
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
      printf("%s   |  ", get_id(getAttribute(code,param)));
  }
}

//Muestro el codigo intermedio de manera correcta.
void toString3DC(Code3D *code)
{
  printf("   %s   |   ", (char*) get_operation_by_id(getCommand(code)));
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
