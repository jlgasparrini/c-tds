/*******************************************************
*Implementacion de Lista de codigos de 3 direcciones   *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations_code.h"
#include "listc3d.h"


/**Constructor de una Lista*/
ListC3D* newListC3D() {
    ListC3D *list = (ListC3D*) malloc(sizeof(ListC3D));
    list->init = NULL;
    list->size = 0;
    return list;
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_listC3D(ListC3D *list, int index) {
    NodeC3D *runner = list->init;
    if ((index >= 0) && (index < size_listC3D(list))) {
        int i;
        for (i = 0; i < index; i++)
            runner = getNext_nodeC3D(runner);
        return getInfo_nodeC3D(runner);
    }
	return NULL; /* This case was added to ensure that this method always return something */
}

/**Metodo que retorna el tamaño de la lista*/
int size_listC3D(ListC3D *list) {
    return list->size;
}

void set_listC3D_int(ListC3D *list,int index,int param, int numb)
{
    NodeC3D *runner = list->init;
    if ((index >= 0) && (index < size_listC3D(list))) {
        int i;
        for (i = 0; i < index - 1; i++)
            runner = getNext_nodeC3D(runner);
        setInt(runner->info, param, numb);
    }
}

/**Metodo para que agrega un Codigo 3D en una posicion en la lista*/
void add_listC3D(ListC3D *list, Code3D *elem, int index) {
    if ((index >= 0) && (index <= size_listC3D(list))) {
        if (index == 0) {
            NodeC3D *node = newNodeC3D_info_next(elem, list->init);
            list->init = node;
        } else {
            NodeC3D *runner = list->init;
            int i;
            for (i = 0; i < index - 1; i++)
                runner = getNext_nodeC3D(runner);
            setNext_nodeC3D(runner, newNodeC3D_info_next(elem, getNext_nodeC3D(runner)));
        }
        list->size++;
    }
}

/**Metodo que borre un Codigo 3D en una posicion especifica*/
void delete_listC3D(ListC3D *list, int index) {
    if ((index >= 0) && (index < size_listC3D(list)))
	{
        NodeC3D *runner = list->init;
        NodeC3D *del = list->init;
        if (index == 0)
            list->init = getNext_nodeC3D(list->init);
		else
		{
            int i;
            for (i = 0; i < index - 1; i++)
                runner = getNext_nodeC3D(runner);
            del = getNext_nodeC3D(runner);
            setNext_nodeC3D(runner, getNext_nodeC3D(del));
        }
        free(del);
        list->size--;
    }
}

/**Metodo que retorna la posicion de un label especifico, buscandolo en la lista*/
int searchByLabel(ListC3D *list, char* label)
{
    NodeC3D *runner = list->init;
    int i;
    for (i = 0; i < size_listC3D(list); i++)
    {
        if (strcmp((char*) get_operation_by_id(getCommand(runner->info)),"LABEL") == 0 && strcmp(getLabel((*runner).info, 1), label) == 0)
            return i;
        runner = getNext_nodeC3D(runner);
    }
    return -1;
}
