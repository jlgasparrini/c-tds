/********************************************************
*Define la estructura y funciones asociadas al manejo   *
*de lista simplemente encadenada                        *
*Una lista esta formada por :                           *
*- inicio   : la cabeza de la lista                     *
*- longitud : la longitud de la lista                   *
*********************************************************/

#ifndef LISTML_H
#define LISTML_H

#include "nodeml.h"
#include <stdbool.h>


typedef struct {
    NodeML    *init;
    int        size;
} ListML;

/*funciones publicas para manipular listas*/

/*constructores*/

ListML* newListML();

/*lectura de informacion*/

MethodL* get_listML(ListML *list, char *id_method);
int size_listML(ListML *list);

/*escritura de informacion*/

void add_listML(ListML *list, MethodL *elem, int index);
void delete_listML(ListML *list, int index);

#endif