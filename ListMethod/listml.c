/*******************************************************
*Implementacion de Lista de codigos de 3 direcciones   *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "listml.h"

ListML* newListML() {
    ListML *new = (ListML*) malloc(sizeof(ListML));
    (*new).init = NULL;
    (*new).size = 0;
    return new;
}

MethodL* get_listML(ListML *list, char *id_method) {
    NodeML *runner = (*list).init;
    bool found = false;
    int i;
    for (i = 0; i < size_listML(list) && !found; i++) {
		if (strcmp(runner->info->id, id_method)== 0){
			found = true;
		}else {
			runner = getNext_NodeML(runner);
		}
    }
    if (found){
		return getInfo_NodeML(runner);
	} else {
		return newMethodL("NULL", "NULL");
	}
}

int size_listML(ListML *list) {
    return (*list).size;
}

void add_listML(ListML *list, MethodL *elem, int index) {
    bool validIndex = (index >= 0) && (index <= size_listML(list));
    if (validIndex) {
        if (index == 0) {
            NodeML *new = newNodeML_info_next(elem, (*list).init);
            (*list).init = new;
        } else {
            int i = 0;
            NodeML *runner = (*list).init;
            while (i < (index - 1)) {
                runner = getNext_NodeML(runner);
                i++;
            }
            setNext_NodeML(runner, newNodeML_info_next(elem, getNext_NodeML(runner)));
        }
        (*list).size++;
    }
}


void delete_listML(ListML *list, int index) {
    bool validIndex = (index >= 0) && (index < size_listML(list));
    if (validIndex) {
        NodeML *runner = (*list).init;
        NodeML *del = (*list).init;
        if (index == 0) {
            (*list).init = getNext_NodeML((*list).init);
        } else {
            int i = 0;
            while (i < (index - 1)) {
                runner = getNext_NodeML(runner);
                i++;
            }
            del = getNext_NodeML(runner);
            setNext_NodeML(runner, getNext_NodeML(getNext_NodeML(runner)));
        }
        free(del);
        (*list).size--;
    }
}
