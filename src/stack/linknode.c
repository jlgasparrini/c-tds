/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linknode.h"

/**Constructor de un Nodo de la Pila vacio*/
NodeStack* newLinkNode() 
{
    NodeStack *node = (NodeStack*) malloc(sizeof(NodeStack));
    node->info = NULL;
    node->next = NULL;
    return node;
}

/**Constructor de un Nodo de la Pila con el campo info*/
NodeStack* newLinkNode_info(char *info)
{
    NodeStack *node = newLinkNode();
    node->info = strdup(info);
    return node;
}

/**Constructor de un Nodo de la Pila con los campos info y next*/
NodeStack* newLinkNode_info_next(char *info, NodeStack *next) 
{
    NodeStack *node = newLinkNode();
    node->info = strdup(info);
    node->next = next;
    return node;
}

/**Metodo que retorna el campo info de un nodo dado*/
char* getInfo_linkNode(NodeStack *node) 
{
    return node->info;
}

/**Metodo que retorna el campo next de un nodo dado*/
NodeStack* getNext_linkNode(NodeStack *node) 
{
    return node->next;
}

/**Metodo que setea el campo info de un nodo dado*/
void setInfo_linkNode(NodeStack *node, char *info) 
{
    node->info = strdup(info);
}

/**Metodo que setea el campo next de un nodo dado*/
void setNext_linkNode(NodeStack *node, NodeStack *next) 
{
    node->next = next;
}
