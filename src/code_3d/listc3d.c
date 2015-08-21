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
    ListC3D *new = (ListC3D*) malloc(sizeof(ListC3D));
    (*new).init = NULL;
    (*new).size = 0;
    return new;
}

/**Metodo que retorna un Codigo 3D dependiendo de una posicion*/
Code3D* get_listC3D(ListC3D *list, int index) {
    NodeC3D *runner = (*list).init;
    if ((index >= 0) && (index < size_listC3D(list))) {
        int i = 0;
        while (i < index) {
            runner = (NodeC3D*) getNext_nodeC3D(runner);
            i++;
        }
        return (Code3D*) getInfo_nodeC3D(runner);
    }
	return NULL; /* This case was added to ensure that this method always return something */
}

/**Metodo que retorna el tamaño de la lista*/
int size_listC3D(ListC3D *list) {
    return (*list).size;
}

void set_listC3D_int(ListC3D *list,int index,int param, int numb)
{
    NodeC3D *runner = (*list).init;
    if ((index >= 0) && (index < size_listC3D(list))) {
        int i = 0;
        while (i < index-1) {
            runner = runner->next;
            i++;
        }
        setInt(runner->info, param, numb);
    }
}

/**Metodo para que agrega un Codigo 3D en una posicion en la lista*/
void add_listC3D(ListC3D *list, Code3D *elem, int index) {
    bool validIndex = (index >= 0) && (index <= size_listC3D(list));
    if (validIndex) {
        if (index == 0) {
            NodeC3D *new = newNodeC3D_info_next(elem, (*list).init);
            (*list).init = new;
        } else {
            int i = 0;
            NodeC3D *runner = (*list).init;
            while (i < (index - 1)) {
                runner = (NodeC3D*) getNext_nodeC3D(runner);
                i++;
            }
            setNext_nodeC3D(runner, newNodeC3D_info_next(elem, (NodeC3D*) getNext_nodeC3D(runner)));
        }
        (*list).size++;
    }
}

/**Metodo que borre un Codigo 3D en una posicion especifica*/
void delete_listC3D(ListC3D *list, int index) {
    if ((index >= 0) && (index < size_listC3D(list)))
	{
        NodeC3D *runner = (*list).init;
        NodeC3D *del = (*list).init;
        if (index == 0)
            (*list).init = (NodeC3D*) getNext_nodeC3D((*list).init);
		else
		{
            int i = 0;
            while (i < (index - 1)) {
                runner = (NodeC3D*) getNext_nodeC3D(runner);
                i++;
            }
            del = getNext_nodeC3D(runner);
            setNext_nodeC3D(runner, getNext_nodeC3D(getNext_nodeC3D(runner)));
        }
        free(del);
        (*list).size--;
    }
}

/**Metodo que retorna la posicion de un label especifico, buscandolo en la lista*/
int searchByLabel(ListC3D *list, char* label)
{
    NodeC3D *runner = (*list).init;
    int i = 0;
    while (i < size_listC3D(list))
    {
        if (strcmp((char*) get_operation_by_id(getCommand(runner->info)),"LABEL") == 0 && strcmp(getLabel((*runner).info, 1), label) == 0)
            return i;
        runner = (NodeC3D*) getNext_nodeC3D(runner);
        i++;
    }
    return -1;
}