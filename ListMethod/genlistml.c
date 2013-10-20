/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include "genlistml.h"
#include <stdlib.h>
#include <stdio.h>

ListMLabel* initL() {
    ListMLabel *new = (ListMLabel*) malloc(sizeof(ListMLabel));
    (*new).labels = newListML();
    return new;
}

void add_MethodL(ListMLabel *listmlabel, MethodL *methodl) {
    add_listML((*listmlabel).labels, methodl, size_listML((*listmlabel).labels));
}

MethodL* get_MethodL(ListMLabel *listmlabel, char *id_method) {
    return get_listML((*listmlabel).labels, id_method);
}

int cantMethodL(ListMLabel *listmlabel) {
    return size_listML((*listmlabel).labels);
}

void insert_MethodL(ListMLabel *listmlabel, char *id_method, char *label_method){
	MethodL *new_methodl = newMethodL(id_method, label_method);
    //Aca estaba este mocaso!!!
	//return add_listML(listmlabel, new_methodl);
	add_listML((*listmlabel).labels, new_methodl, size_listML((*listmlabel).labels));
}

char* get_Label(ListMLabel *listmlabel, char *id_method) {
	return ((get_MethodL(listmlabel, id_method))->label);
}
