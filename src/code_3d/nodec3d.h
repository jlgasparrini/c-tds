/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un Nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el Nodo                                        *
*- siguiente    :   un puntero al siguiente Nodo                                                *
*************************************************************************************************/

#ifndef NODEC3D_H
#define NODEC3D_H

#include "code_3d.h"

typedef struct NC3D {
    Code3D *info;
    struct NC3D *next;
} NodeC3D;

/*funciones publicas para manipular Nodes*/

/*constructores*/
NodeC3D* new_node_c3d();
NodeC3D* new_node_c3d_info(Code3D *info);
NodeC3D* new_node_c3d_info_next(Code3D *info, NodeC3D *next);

/*lectura de informacion*/
Code3D* get_info_node_c3d(NodeC3D *node);
NodeC3D* get_next_node_c3d(NodeC3D *node);

/*escritura de informacion*/
void set_info_node_c3d(NodeC3D *node, Code3D *info);
void set_next_node_c3d(NodeC3D *node, NodeC3D *next);

#endif
