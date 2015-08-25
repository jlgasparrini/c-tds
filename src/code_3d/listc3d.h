/********************************************************
* Define la estructura y funciones asociadas al manejo  *
* de lista simplemente encadenada                       *
* La lista esta formada por:                            *
* - init: cabeza de la lista                            *
* - size: longitud de la lista                          *
********************************************************/

#ifndef LISTC3D_H
#define LISTC3D_H

#include "nodec3d.h"

typedef struct {
    NodeC3D    *init;
    int        size;
} ListC3D;

/** Initializes and returns a new ListC3D */
ListC3D* new_list_c3d();

/** Returns the Code3D at "index" position of "list" */
Code3D* get_list_c3d(ListC3D *list, int index);

/** Returns the size of the list */
int size_list_c3d(ListC3D *list);

void set_list_c3d_int(ListC3D *list,int index,int param, int numb);

/** Inserts a new Code in the list at the position specified by "index" */
void add_list_c3d(ListC3D *list, Code3D *code, int index);

/** Deletes the Code3D at the "index" position */
void delete_list_c3d(ListC3D *list, int index);

/** Search one label in the list and return the position of this*/
int search_by_label(ListC3D *list, char* label);

#endif
