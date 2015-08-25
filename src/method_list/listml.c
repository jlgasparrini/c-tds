/*******************************************************
*Implementacion de Lista de codigos de 3 direcciones   *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listml.h"

ListML* new_list_ml()
{
    ListML *list = (ListML*) malloc(sizeof(ListML));
    list->init = NULL;
    list->size = 0;
    return list;
}

MethodL* get_list_ml(ListML *list, char *id_method)
{
    NodeML *runner = list->init;
    bool found = false;
    int i;
    for (i = 0; i < size_list_ml(list) && !found; i++) {
		if (strcmp(runner->info->id, id_method) == 0)
			found = true;
		else
			runner = get_next_node_ml(runner);
    }
    if (found)
		return get_info_node_ml(runner);
	return new_method_l("NULL", "NULL");
}

int size_list_ml(ListML *list) {
    return list->size;
}

void add_list_ml(ListML *list, MethodL *elem, int index) 
{
    if ((index >= 0) && (index <= size_list_ml(list)))
	{
        if (index == 0)
            list->init = new_node_ml_info_next(elem, list->init);        
		else 
		{
            NodeML *runner = list->init;
            int i;
            for (i = 0; i < index - 1; i++)
                runner = get_next_node_ml(runner);
            set_next_node_ml(runner, new_node_ml_info_next(elem, get_next_node_ml(runner)));
        }
        list->size++;
    }
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
