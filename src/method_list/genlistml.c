/************************************************************************
*Implementacion de generador de comandos de 3 direcciones               *
************************************************************************/

#include "genlistml.h"
#include <stdlib.h>
#include <stdio.h>

ListMLabel* init_list_m() 
{
    ListMLabel *list = (ListMLabel*) malloc(sizeof(ListMLabel));
    list->labels = new_list_ml();
    return list;
}

int size_method_list(ListMLabel *listmlabel) 
{
    return size_list_ml(listmlabel->labels);
}

void insert_method_list(ListMLabel *listmlabel, char *id_method, char *label_method)
{
	MethodL *new_methodl = new_method_l(id_method, label_method);
	add_list_ml(listmlabel->labels, new_methodl);
}

char* get_label_ml(ListMLabel *listmlabel, char *id_method) 
{
	return get_list_ml(listmlabel->labels, id_method)->label;
}
