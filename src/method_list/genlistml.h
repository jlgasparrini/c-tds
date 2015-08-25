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

ListMLabel* initL();

void add_MethodL(ListMLabel *listmlabel, MethodL *methodl); 
int size_MethodL(ListMLabel *listmlabel);
void insert_MethodL(ListMLabel *listmlabel, char *id_method, char *label_method);
char* get_Label(ListMLabel *listmlabel, char *id_method);

#endif
