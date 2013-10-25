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

NodeStack* newLinkNode_empty() 
{
    NodeStack *new = (NodeStack*) malloc(sizeof(NodeStack));
    new->info = NULL;
    new->next = NULL;
    return new;
}

NodeStack* newLinkNode_info(char *info)
{
    NodeStack *new = newLinkNode_empty();
    new->info = newchar(info);
    return new;
}

NodeStack* newLinkNode_info_next(char *info, NodeStack *next) 
{
    NodeStack *new = newLinkNode_info(info);
    new->next = next;
    return new;
}

char* getInfo_linkNode(NodeStack *node) 
{
    return node->info;
}

NodeStack* getNext_linkNode(NodeStack *node) 
{
    return node->next;
}

void setInfo_linkNode(NodeStack *node, char *info) 
{
    node->info = newchar(info);
}

void setNext_linkNode(NodeStack *node, NodeStack *next) 
{
    node->next = next;
}
