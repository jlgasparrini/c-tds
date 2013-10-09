/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el nodo                                        *
*- siguiente    :   un puntero al siguiente nodo                                                *
*************************************************************************************************/

#ifndef LINKNODE_H
#define LINKNODE_H

#include "../SymbolsTable/Attribute.h"
#include "label.h"


struct NodeStack {
    Label *info;
    struct NodeStack *next;
};

typedef struct NodeStack NodeStack;

/*funciones publicas para manipular nodos*/

/*constructores*/

NodeStack* newLinkNode_empty();
NodeStack* newLinkNode_info(char *info, Attribute *eval);
NodeStack* newLinkNode_info_next(char *info, Attribute *eval, NodeStack *next);

/*lectura de informacion*/

Label* getInfo_linkNode(NodeStack *node);
NodeStack* getNext_linkNode(NodeStack *node);

/*escritura de informacion*/
void setInfo_linkNode(NodeStack *node, char *info, Attribute *eval);
void setNext_linkNode(NodeStack *node, NodeStack *next);

#endif
