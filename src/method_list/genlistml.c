/************************************************************************
 *Implementacion de generador de comandos de 3 direcciones              *
 ************************************************************************/

#include "genlistml.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ListMLabel* init_list_m()
{
  ListMLabel *list = (ListMLabel*) malloc(sizeof(ListMLabel));
  list->init = NULL;
  list->size = 0;
  return list;
}

int size_method_list(ListMLabel *list)
{
  return list->size;
}

/* Return true iff list is empty*/
bool is_empty_ml(ListMLabel *list)
{
  return list->size == 0;
}

void insert_method_list(ListMLabel *list, char *id_method, char *label_method)
{
  MethodL *m_label = new_method_l(id_method, label_method);
  if (is_empty_ml(list))
    list->init = new_node_ml_info_next(m_label, list->init);
  else
  {
    NodeML *runner = list->init;
    int i;
    for (i = 0; i < size_method_list(list) - 1; i++)
      runner = get_next_node_ml(runner);
    set_next_node_ml(runner, new_node_ml_info_next(m_label, get_next_node_ml(runner)));
  }
  list->size++;
}

char* get_label_ml(ListMLabel *list, char *id_method)
{
  NodeML *runner = list->init;
  bool found = false;
  int i;
  for (i = 0; i < size_method_list(list) && !found; i++) 
  {
    if (strcmp(runner->info->id, id_method) == 0)
      found = true;
    else
      runner = get_next_node_ml(runner);
  }
  if (found)
    return get_info_node_ml(runner)->label;
  return new_method_l("NULL", "NULL")->label;
}

void delete_list_ml(ListMLabel *list, int index) {
  if ((index >= 0) && (index < size_method_list(list)))
  {
    NodeML *runner = list->init;
    NodeML *to_delete = list->init;
    if (index == 0)
      list->init = get_next_node_ml(list->init);
    else
    {
      int i;
      for (i = 0; i < index - 1; ++i)
        runner = get_next_node_ml(runner);
      to_delete = get_next_node_ml(runner);
      set_next_node_ml(runner, get_next_node_ml(to_delete));
    }
    free(to_delete);
    list->size--;
  }
}
