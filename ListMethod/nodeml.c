/********************************************************
*Implementacion de NodeML                              *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodeml.h"

NodeML* newNodeML_empty() {
    NodeML *new = (NodeML*) malloc(sizeof(NodeML));
    new->info = NULL;
    new->next = NULL;
    return new;
}

NodeML* newNodeML_info(MethodL *info) {
    NodeML *new = newNodeML_empty();
    new->info = info;
    return new;
}

NodeML* newNodeML_info_next(MethodL *info, NodeML *next) {
    NodeML *new = newNodeML_info(info);
    new->next = next;
    return new;
}

MethodL* getInfo_NodeML(NodeML *node) {
    return node->info;
}

NodeML* getNext_NodeML(NodeML *node) {
    return node->next;
}

void setInfo_NodeML(NodeML *node, MethodL *info) {
    node->info = info;
}

void setNext_NodeML(NodeML *node, NodeML *next) {
    node->next = next;
}
