/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un Nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el Nodo                                        *
*- siguiente    :   un puntero al siguiente Nodo                                                *
*************************************************************************************************/

#ifndef NODEML_H
#define NODEML_H

#include "methodl.h"

struct NodeML {
    MethodL *info;
    struct NodeML *next;
};

typedef struct NodeML NodeML;

/*funciones publicas para manipular Nodes*/

/*constructores*/

NodeML* newNodeML_empty();
NodeML* newNodeML_info(MethodL *info);
NodeML* newNodeML_info_next(MethodL *info, NodeML *next);

/*lectura de informacion*/

MethodL* getInfo_NodeML(NodeML *node);
NodeML* getNext_NodeML(NodeML *node);

/*escritura de informacion*/
void setInfo_NodeML(NodeML *node, MethodL *info);
void setNext_NodeML(NodeML *node, NodeML *next);

#endif