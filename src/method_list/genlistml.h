/************************************************************************
*Define la estructura  y funciones asociadas para un generador de       *
*codigo de 3 direcciones                                              	*
*************************************************************************/

#ifndef GENLISTML_H
#define GENLISTML_H

#include "nodeml.h"
#include <stdbool.h>

typedef struct {
	NodeML    *init;
	int        size;
} ListMLabel;


ListMLabel* init_list_m();

int size_method_list(ListMLabel *list);
void insert_method_list(ListMLabel *list, char *id_method, char *label_method);
char* get_label_ml(ListMLabel *list, char *id_method);

void delete_list_ml(ListMLabel *list, int index);
#endif
