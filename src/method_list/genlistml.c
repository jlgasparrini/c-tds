/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include "genlistml.h"
#include <stdlib.h>
#include <stdio.h>

ListMLabel* initL() 
{
    ListMLabel *list = (ListMLabel*) malloc(sizeof(ListMLabel));
    list->labels = newListML();
    return list;
}

void add_MethodL(ListMLabel *listmlabel, MethodL *methodl) 
{
    add_listML(listmlabel->labels, methodl, size_listML(listmlabel->labels));
}

int size_MethodL(ListMLabel *listmlabel) 
{
    return size_listML(listmlabel->labels);
}

void insert_MethodL(ListMLabel *listmlabel, char *id_method, char *label_method)
{
	MethodL *new_methodl = newMethodL(id_method, label_method);
	add_listML(listmlabel->labels, new_methodl, size_listML(listmlabel->labels));
}

char* get_Label(ListMLabel *listmlabel, char *id_method) 
{
	return get_listML(listmlabel->labels, id_method)->label;
}
