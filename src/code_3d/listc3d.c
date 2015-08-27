/*******************************************************
*Implementacion de Lista de codigos de 3 direcciones   *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations_code.h"
#include "listc3d.h"


/**Constructor de una Lista*/
ListC3D* new_list_c3d() {
    ListC3D *list = (ListC3D*) malloc(sizeof(ListC3D));
    list->init = NULL;
    list->size = 0;
    return list;
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_list_c3d(ListC3D *list, int index) {
    NodeC3D *runner = list->init;
    if ((index >= 0) && (index < size_list_c3d(list))) {
        int i;
        for (i = 0; i < index; i++)
            runner = get_next_node_c3d(runner);
        return get_info_node_c3d(runner);
    }
	return NULL; /* This case was added to ensure that this method always return something */
}

/* Return true iff list is empty*/
bool is_empty_c3d(ListC3D *list)
{
    return list->size == 0;
}

/**Metodo que retorna el tamaño de la lista*/
int size_list_c3d(ListC3D *list) {
    return list->size;
}

void set_list_c3d_int(ListC3D *list, int index, int param, int numb)
{
    if ((index >= 0) && (index < size_list_c3d(list))) {
        NodeC3D *runner = list->init;
        int i;
        for (i = 0; i < index - 1; i++)
            runner = get_next_node_c3d(runner);
        set_int(runner->info, param, numb);
    }
}

/**Metodo para que agrega un Codigo 3D en una posicion en la lista*/
void add_list_c3d(ListC3D *list, Code3D *elem) {
    if (is_empty_c3d(list)) {
        NodeC3D *node = new_node_c3d_info(elem);
        list->init = node;
    } else {
        NodeC3D *runner = list->init;
        int i;
        for (i = 0; i < size_list_c3d(list) - 1; i++)
            runner = get_next_node_c3d(runner);
        set_next_node_c3d(runner, new_node_c3d_info_next(elem, get_next_node_c3d(runner)));
    }
    list->size++;
}

/**Metodo que borre un Codigo 3D en una posicion especifica*/
void delete_list_c3d(ListC3D *list, int index) {
    if ((index >= 0) && (index < size_list_c3d(list)))
	{
        NodeC3D *runner = list->init;
        NodeC3D *del = list->init;
        if (index == 0)
            list->init = get_next_node_c3d(list->init);
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

/**Metodo que retorna la posicion de un label especifico, buscandolo en la lista*/
int search_by_label(ListC3D *list, char* label)
{
    NodeC3D *runner = list->init;
    int i;
    for (i = 0; i < size_list_c3d(list); i++)
    {
        if (strcmp((char*) get_operation_by_id(get_command(runner->info)),"LABEL") == 0 && strcmp(get_label(runner->info, 1), label) == 0)
            return i;
        runner = get_next_node_c3d(runner);
    }
    return -1;
}
