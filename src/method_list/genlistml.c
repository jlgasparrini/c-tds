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
  ListML *listml = (ListML*) malloc(sizeof(ListML));
  listml->init = NULL;
  listml->size = 0;
  list->labels = listml;
  return list;
}

int size_list_ml(ListML *list) {
  return list->size;
}

int size_method_list(ListMLabel *listmlabel)
{
  return size_list_ml(listmlabel->labels);
}

/* Return true iff list is empty*/
bool is_empty_ml(ListML *list)
{
  return list->size == 0;
}

void insert_method_list(ListMLabel *list, char *id_method, char *label_method)
{
  MethodL *elem = new_method_l(id_method, label_method);
  if (is_empty_ml(list->labels))
    list->labels->init = new_node_ml_info_next(elem, list->labels->init);
  else
  {
    NodeML *runner = list->labels->init;
    int i;
    for (i = 0; i < size_list_ml(list->labels) - 1; i++)
      runner = get_next_node_ml(runner);
    set_next_node_ml(runner, new_node_ml_info_next(elem, get_next_node_ml(runner)));
  }
  list->labels->size++;
}

char* get_label_ml(ListMLabel *list, char *id_method)
{
  NodeML *runner = list->labels->init;
  bool found = false;
  int i;
  for (i = 0; i < size_list_ml(list->labels) && !found; i++) {
    if (strcmp(runner->info->id, id_method) == 0)
      found = true;
    else
      runner = get_next_node_ml(runner);
  }
  if (found)
    return get_info_node_ml(runner)->label;
  return new_method_l("NULL", "NULL")->label;
}

void delete_list_ml(ListML *list, int index) {
  bool validIndex = (index >= 0) && (index < size_list_ml(list));
  if (validIndex) {
    NodeML *runner = list->init;
    NodeML *del = list->init;
    if (index == 0) {
      list->init = get_next_node_ml(list->init);
    } else {
      int i;
      for (i = 0; i < index - 1; ++i)
        runner = get_next_node_ml(runner);
      del = get_next_node_ml(runner);
      set_next_node_ml(runner, get_next_node_ml(del));
    }
    free(del);
    list->size--;
  }
}
