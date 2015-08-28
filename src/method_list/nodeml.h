/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un Nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el Nodo                                        *
*- siguiente    :   un puntero al siguiente Nodo                                                *
*************************************************************************************************/

#ifndef NODEML_H
#define NODEML_H

#include "methodl.h"

typedef struct NML {
    MethodL *info;
    struct NML *next;
} NodeML;

/*funciones publicas para manipular Nodes*/

/*constructores*/

NodeML* new_node_ml();
NodeML* new_node_ml_info(MethodL *info);
NodeML* new_node_ml_info_next(MethodL *info, NodeML *next);

/*lectura de informacion*/

MethodL* get_info_node_ml(NodeML *node);
NodeML* get_next_node_ml(NodeML *node);

/*escritura de informacion*/
void set_info_node_ml(NodeML *node, MethodL *info);
void set_next_node_ml(NodeML *node, NodeML *next);

#endif
