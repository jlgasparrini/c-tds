/*******************************************************
*Implementacion de Lista de codigos de 3 direcciones   *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "listc3d.h"

ListC3D* newListC3D() {
    ListC3D *new = (ListC3D*) malloc(sizeof(ListC3D));
    (*new).init = NULL;
    (*new).size = 0;
    return new;
}

Code3D* get_listC3D(ListC3D *list, int index) {
    NodeC3D *runner = (*list).init;
    if ((index >= 0) && (index < size_listC3D(list))) {
        int i = 0;
        while (i < index) {
            runner = (NodeC3D*) getNext_NodeC3D(runner);
            i++;
        }
        return (Code3D*) getInfo_nodeC3D(runner);
    } 
	return NULL; /* This case was added to ensure that this method always return something */
}

int size_listC3D(ListC3D *list) {
    return (*list).size;
}

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
                runner = (NodeC3D*) getNext_NodeC3D(runner);
                i++;
            }
            setNext_nodeC3D(runner, newNodeC3D_info_next(elem, (NodeC3D*) getNext_NodeC3D(runner)));
        }
        (*list).size++;
    }
}

void delete_listC3D(ListC3D *list, int index) {
    if ((index >= 0) && (index < size_listC3D(list)))
	{
        NodeC3D *runner = (*list).init;
        NodeC3D *del = (*list).init;
        if (index == 0)
            (*list).init = (NodeC3D*) getNext_NodeC3D((*list).init);
		else
		{
            int i = 0;
            while (i < (index - 1)) {
                runner = (NodeC3D*) getNext_NodeC3D(runner);
                i++;
            }
            del = getNext_NodeC3D(runner);
            setNext_nodeC3D(runner, getNext_NodeC3D(getNext_NodeC3D(runner)));
        }
        free(del);
        (*list).size--;
    }
}

//Toma una posicion y comienza a buscar el label pasado por parametro dentro del codigo intermedio!
int searchByLabel(ListC3D *list, char* label)
{
    NodeC3D *runner = (*list).init;
    int i = 0;
    while (i <= size_listC3D(list)) 
    {
        //printf("buscando %s en la posicion %d\n", label, i);
        runner = (NodeC3D*) getNext_NodeC3D(runner);
        if (strcmp(getCodeByID(getCommand(runner->info)),"LABEL") == 0 && strcmp(getLabel((*runner).info, 1), label) == 0){
            //printf("encontre %s en la posicion %d\n", label, i);
            return i+1;}
        i++;
    }
    printf("Va a largar segmentation fault!!!!! FUCK -.- no se encontro %s\n", label);
    return -1;
}
