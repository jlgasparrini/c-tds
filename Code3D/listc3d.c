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
    bool validIndex = (index >= 0) && (index < size_listC3D(list));
    if (validIndex) {
        int i = 0;
        while (i < index) {
            runner = getNext_nodeC3D(runner);
            i++;
        }
        return getInfo_nodeC3D(runner);
    } 
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
                runner = getNext_nodeC3D(runner);
                i++;
            }
            NodeC3D *new = newNodeC3D_info_next(elem, getNext_nodeC3D(runner));
            defineNext_nodeC3D(runner, new);
        }
        (*list).size = size_listC3D(list) + 1;
    }
}


void delete_listC3D(ListC3D *list, int index) {
    bool validIndex = (index >= 0) && (index < size_listC3D(list));
    if (validIndex) {
        NodeC3D *runner = (*list).init;
        NodeC3D *del = (*list).init;
        if (index == 0) {
            (*list).init = getNext_nodeC3D((*list).init);
        } else {
            int i = 0;
            while (i < (index - 1)) {
                runner = getNext_nodeC3D(runner);
                i++;
            }
            del = getNext_nodeC3D(runner);
            defineNext_nodeC3D(runner, getNext_nodeC3D(getNext_nodeC3D(runner)));
        }
        free(del);
        (*list).size = size_listC3D(list) - 1;
    }
}
