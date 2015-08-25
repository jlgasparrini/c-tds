/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el nodo                                        *
*- siguiente    :   un puntero al siguiente nodo                                                *
*************************************************************************************************/

#ifndef LINKNODE_H
#define LINKNODE_H

typedef struct NodeStack {
    char *info;
    struct NodeStack *next;
} NodeStack;

/*funciones publicas para manipular nodos*/

/*constructores*/

NodeStack* new_link_node();
NodeStack* new_link_node_info(char *info);
NodeStack* new_link_node_info_next(char *info, NodeStack *next);

/*lectura de informacion*/

char* get_info_link_node(NodeStack *node);
NodeStack* get_next_link_node(NodeStack *node);

/*escritura de informacion*/
void set_info_link_node(NodeStack *node, char *info);
void set_next_link_node(NodeStack *node, NodeStack *next);

#endif
