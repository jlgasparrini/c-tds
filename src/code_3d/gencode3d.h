/************************************************************************
 *Define la estructura  y funciones asociadas para un generador de      *
 *codigo de 3 direcciones                                              	*
 ************************************************************************/

#ifndef GENCODE3D_H
#define GENCODE3D_H

#include "nodec3d.h"

typedef struct {
  NodeC3D    *init;
  int        size;
} ListC3D;

/**Constructor de una Lista*/
ListC3D* init_list_c3D();

/**Funcion de Escritura de la Lista*/
void add_code(ListC3D *list, Code3D *code);

/**Funciones de Acceso a la Lista*/
Code3D* get_code(ListC3D *list, int index);
int code_size(ListC3D *list);

/**/
void set_code_int(ListC3D *list, int index, int param, int numb);

/** Funciones de Escritura de la Lista de un Codigo Concreto*/
void add_code_label(ListC3D *list, Code3D *code, char *label);
void add_code_label_cond(ListC3D *list, Code3D *code, Attribute *attri1, char *label_jump_to);

void add_assignation(ListC3D *list, Attribute *attri1,  Attribute *attri_result);
void add_print(ListC3D *list, Code3D *code, Attribute *attr);
void add_method_call(ListC3D *list, Code3D *code,  Attribute *attri1, Attribute *attri_result);

void add_code_externinvk(ListC3D *list, Code3D *code,char *label,  char* type);
void add_param_externinvk(ListC3D *list, Code3D *code, Attribute *attr, int param_number);

/**Funcion de Borrado de un Codigo de la Lista*/
void delete_code(ListC3D *list, int index);

/**Funcion de Muestreo de la Lista*/
void show_c3D(ListC3D *list);

/** Search one label in the list and return the position of this*/
int search_by_label(ListC3D *list, char *label);
#endif
