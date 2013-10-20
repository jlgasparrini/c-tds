/********************************************************
*Define la estructura y funcione asociadas al manejo    *
*de lista simplemente encadenada                        *
*Una lista esta formada por :                           *
*- inicio   : la cabeza de la lista                     *
*- longitud : la longitud de la lista                   *
*********************************************************/

#ifndef LISTC3D_H
#define LISTC3D_H

#include <stdbool.h>
#include "nodec3d.h"
#include "../SymbolsTable/Attribute.h"


typedef struct {
    NodeC3D    *init;
    int        size;
} ListC3D;

/*funciones publicas para manipular listas*/

/*constructores*/

ListC3D* newListC3D();

/*lectura de informacion*/

Code3D* get_listC3D(ListC3D *list, int index);
int size_listC3D(ListC3D *list);

/*escritura de informacion*/

void add_listC3D(ListC3D *list, Code3D *code, int index);
void delete_listC3D(ListC3D *list, int index);

#endif
