/************************************************************************
*Define la estructura  y funciones asociadas para un generador de       *
*codigo de 3 direcciones                                              *
*************************************************************************/

#ifndef GENLISTML_H
#define GENLISTML_H

#include "listml.h"

typedef struct {
    ListML *labels;
} ListMLabel;

ListMLabel* init_list_m();

int size_method_list(ListMLabel *listmlabel);
void insert_method_list(ListMLabel *listmlabel, char *id_method, char *label_method);
char* get_label_ml(ListMLabel *listmlabel, char *id_method);

#endif
