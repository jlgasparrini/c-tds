/********************************************************
* Define la estructura y funciones asociadas al manejo  *
* de lista simplemente encadenada                       *
* La lista esta formada por:                            *
* - init: cabeza de la lista                            *
* - size: longitud de la lista                          *
********************************************************/

#ifndef LISTC3D_H
#define LISTC3D_H

#include <stdbool.h>
#include "nodec3d.h"
#include "../SymbolsTable/Attribute.h"

typedef struct {
    NodeC3D    *init;
    int        size;
} ListC3D;

/* Initializes and returns a new ListC3D */
ListC3D* newListC3D();

/* Returns the Code3D at "index" position of "list" */
Code3D* get_listC3D(ListC3D *list, int index);

/* Returns the size of the list */
int size_listC3D(ListC3D *list);

/* Inserts a new Code in the list at the position specified by "index" */
void add_listC3D(ListC3D *list, Code3D *code, int index);

/* Deletes the Code3D at the "index" position */
void delete_listC3D(ListC3D *list, int index);

#endif
