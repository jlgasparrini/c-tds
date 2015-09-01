/************************************************************************
 *Implementacion de generador de comandos de 3 direcciones              *
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gencode3d.h"
#include "operations_code.h"
#include "../SymbolsTable/Utils.h"


/**Constructor de la Lista de Codigos 3D*/
ListC3D* init_list_c3D()
{
  ListC3D *list = (ListC3D*) malloc(sizeof(ListC3D));
  list->init = NULL;
  list->size = 0;
  return list;
}

/* Return true iff list is empty*/
bool is_empty_c3d(ListC3D *list)
{
  return list->size == 0;
}

/**Metodo que agrega un Codigo 3D a la lista*/
void add_code(ListC3D *list, Code3D *elem)
{
  if (is_empty_c3d(list)) {
    NodeC3D *node = new_node_c3d_info(elem);
    list->init = node;
  } else {
    NodeC3D *runner = list->init;
    int i;
    for (i = 0; i < code_size(list) - 1; i++)
      runner = get_next_node_c3d(runner);
    set_next_node_c3d(runner, new_node_c3d_info_next(elem, get_next_node_c3d(runner)));
  }
  list->size++;
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_code(ListC3D *list, int index)
{
  NodeC3D *runner = list->init;
  if ((index >= 0) && (index < code_size(list))) {
    int i;
    for (i = 0; i < index; i++)
      runner = get_next_node_c3d(runner);
    return get_info_node_c3d(runner);
  }
  return NULL; /* This case was added to ensure that this method always return something */
}

/**Metodo de retorna el tamaño de la Lista*/
int code_size(ListC3D *list)
{
  return list->size;
}

void set_code_int(ListC3D *list,int index,int param, int numb)
{
  if ((index >= 0) && (index < code_size(list))) {
    NodeC3D *runner = list->init;
    int i;
    for (i = 0; i < index; i++)
      runner = get_next_node_c3d(runner);
    set_int(runner->info, param, numb);
  }
}

/**Metodo que a base de un Codigo 3D y un label, setea el codigo y lo agrega a la Lista*/
void add_code_label(ListC3D *list, Code3D *code, char *label)
{
  set_code_label(code, label);
  add_code(list, code);
}

/**Metodo que a base de un Codigo 3D, un Atributo y un label, setea el codigo y lo agrega a la Lista*/
void add_code_label_cond(ListC3D *list, Code3D *code, Attribute *attri1, char *label_to_jump)
{
  set_code_label_cond(code, attri1, label_to_jump);
  add_code(list, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_assignation(ListC3D *list, Attribute *attri1, Attribute *attriRes)
{
  Code3D *code;
  switch (get_attribute_type(attri1))
  {
    case Int:   code = new_code(ASSIGNATION_INT); break;
    case Float: code = new_code(ASSIGNATION_FLOAT); break;
    case Bool:  code = new_code(ASSIGNATION_BOOL); break;
    default: break;
  }
  set_c2D(code, attri1, attriRes);
  add_code(list, code);
}

/**Metodo que a base de un Codigo 3D y un Atributo, setea el codigo y lo agrega a la Lista*/
void add_print(ListC3D *list, Code3D *code, Attribute *attr)
{
  set_c1D(code, attr);
  add_code(list, code);
}

/**Metodo que a base de un Codigo 3D y dos Atributos, setea el codigo y lo agrega a la Lista*/
void add_method_call(ListC3D *list, Code3D *code,  Attribute *attri1,  Attribute *attriRes)
{	/**Uses a copy of attr1 because the parameter passing must be by value */
  set_c2D(code, attri1, attriRes);
  add_code(list, code);
}

void add_code_externinvk(ListC3D *list, Code3D *code,char *label,  char* type)
{
  set_code_label(code, label);
  set_label(code, 2, type);
  add_code(list, code);
}

void add_param_externinvk(ListC3D *list, Code3D *code, Attribute *attr, int paramNumber)
{
  set_attribute(code, 1, attr);
  set_int(code, 2, paramNumber);
  set_null(code, 3);
  add_code(list, code);
}

/**Metodo que borra un Codigo 3D de la lista dependiendo una posicion*/
void delete_code(ListC3D *list, int index)
{
  if ((index >= 0) && (index < code_size(list)))
  {
    NodeC3D *runner = list->init;
    NodeC3D *del = list->init;
    if (index == 0)
      list->init = get_next_node_c3d(runner);
    else
    {
      int i;
      for (i = 0; i < index - 1; i++)
        runner = get_next_node_c3d(runner);
      del = get_next_node_c3d(runner);
      set_next_node_c3d(runner, get_next_node_c3d(del));
    }
    free(del);
    list->size--;
  }
}

/**Prints on the screen the 3d code that contains the list list */
void show_c3D(ListC3D *list)
{
  int code_amount = code_size(list);
  printf("Lista de codigos de 3 direcciones:\n");
  printf("---------------------------------------------------------------------------\n");
  printf("     Operacion     |       res       |       arg1       |       arg2       \n");
  printf("---------------------------------------------------------------------------\n");
  int i;
  for (i = 0; i < code_amount; i++)
    to_string_c3D(get_code(list, i));
}

/**Metodo que retorna la posicion de un label especifico, buscandolo en la lista*/
int search_by_label(ListC3D *list, char* label)
{
  NodeC3D *runner = list->init;
  int i;
  for (i = 0; i < list->size; i++)
  {
    if (strcmp((char*) get_operation_by_id(get_command(runner->info)),"LABEL") == 0 && strcmp(get_label(runner->info, 1), label) == 0)
      return i;
    runner = get_next_node_c3d(runner);
  }
  return -1;
}
