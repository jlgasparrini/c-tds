/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linknode.h"

char* newchar(char *label) 
{
    char *new = (char*) malloc(sizeof(char));
    new = label;
    return new;
}

/**Constructor de un Nodo de la Pila vacio*/
NodeStack* newLinkNode_empty() 
{
    NodeStack *new = (NodeStack*) malloc(sizeof(NodeStack));
    new->info = NULL;
    new->next = NULL;
    return new;
}

/**Constructor de un Nodo de la Pila con el campo info*/
NodeStack* newLinkNode_info(char *info)
{
    NodeStack *new = newLinkNode_empty();
    new->info = newchar(info);
    return new;
}

/**Constructor de un Nodo de la Pila con los campos info y next*/
NodeStack* newLinkNode_info_next(char *info, NodeStack *next) 
{
    NodeStack *new = newLinkNode_info(info);
    new->next = next;
    return new;
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
    node->info = newchar(info);
}

/**Metodo que setea el campo next de un nodo dado*/
void setNext_linkNode(NodeStack *node, NodeStack *next) 
{
    node->next = next;
}
