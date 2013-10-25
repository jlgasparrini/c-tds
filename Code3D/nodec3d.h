/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un Nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el Nodo                                        *
*- siguiente    :   un puntero al siguiente Nodo                                                *
*************************************************************************************************/

#ifndef NODEC3D_H
#define NODEC3D_H

#include "code3d.h"

typedef struct NC3D {
    Code3D *info;
    struct NC3D *next;
} NodeC3D;

/*funciones publicas para manipular Nodes*/

/*constructores*/

NodeC3D* newNodeC3D_empty();
NodeC3D* newNodeC3D_info(Code3D *info);
NodeC3D* newNodeC3D_info_next(Code3D *info, NodeC3D *next);

/*lectura de informacion*/

//Code3D* getInfo_NodeC3D(NodeC3D *node); NO ESTA IMPLEMENTADOOO!!! -,-
NodeC3D* getNext_NodeC3D(NodeC3D *node);

/*escritura de informacion*/
void setInfo_NodeC3D(NodeC3D *node, Code3D *info);
void setNext_NodeC3D(NodeC3D *node, NodeC3D *next);

#endif
