/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el nodo                                        *
*- next		    :   un puntero al siguiente nodo                                                *
*************************************************************************************************/

#ifndef LINKNODEOFFSET_H
#define LINKNODEOFFSET_H

typedef struct NodeStackOffset {
    int *info;
    struct NodeStackOffset *next;
} NodeStackOffset;

/*funciones publicas para manipular nodos*/

/*constructores*/

NodeStackOffset* new_link_node_offset();
NodeStackOffset* new_link_node_offset_info(int);
NodeStackOffset* new_link_node_offset_info_next(int, NodeStackOffset*);

/*lectura de informacion*/

int get_info_link_node_offset(NodeStackOffset*);
NodeStackOffset* get_next_link_node_offset(NodeStackOffset*);

/*escritura de informacion*/
void set_info_link_node_offset(NodeStackOffset*, int);
void set_next_link_node_offset(NodeStackOffset*, NodeStackOffset*);

#endif
