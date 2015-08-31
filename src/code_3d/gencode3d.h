/************************************************************************
 *Define la estructura  y funciones asociadas para un generador de       *
 *codigo de 3 direcciones                                              *
 *************************************************************************/

#ifndef GENCODE3D_H
#define GENCODE3D_H

#include "nodec3d.h"

typedef struct {
  NodeC3D    *init;
  int        size;
} ListC3D;

typedef struct {
  ListC3D *codes;
} LCode3D;

/**Constructor de una Lista*/
LCode3D* init_list_c3D();

/**Funcion de Escritura de la Lista*/
void add_code(LCode3D *lcode3d, Code3D *code);

/**Funciones de Acceso a la Lista*/
Code3D* get_code(LCode3D *lcode3d, int index);
int code_size(LCode3D *lcode3d);

/**/
void set_code_int(LCode3D *lcode3d,int index,int param, int numb);

/** Funciones de Escritura de la Lista de un Codigo Concreto*/
void add_code_label(LCode3D *lcode3d, Code3D *code, char *label);
void add_code_label_cond(LCode3D *lcode3d, Code3D *code, Attribute *attri1, char *labelJumpTo);

void add_assignation(LCode3D *lcode3d, Attribute *attri1,  Attribute *attriRes);
void add_print(LCode3D *lcode3d, Code3D *code, Attribute *attr);
void add_method_call(LCode3D *lcode3d, Code3D *code,  Attribute *attri1, Attribute *attriRes);

void add_code_externinvk(LCode3D *lcode3d, Code3D *code,char *label,  char* type);
void add_param_externinvk(LCode3D *lcode3d, Code3D *code, Attribute *attr, int paramNumber);

/**Funcion de Borrado de un Codigo de la Lista*/
void delete_code(LCode3D *lcode3d, int index);

/**Funcion de Muestreo de la Lista*/
void show_c3D(LCode3D *lcode3d);

/** Search one label in the list and return the position of this*/
int search_by_label(ListC3D *list, char* label);
#endif
