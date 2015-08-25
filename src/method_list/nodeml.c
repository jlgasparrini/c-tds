/********************************************************
*Implementacion de NodeML                              *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodeml.h"

NodeML* newNodeML() {
    NodeML *node = (NodeML*) malloc(sizeof(NodeML));
    node->info = NULL;
    node->next = NULL;
    return node;
}

NodeML* newNodeML_info(MethodL *info) {
    NodeML *node = newNodeML();
    node->info = info;
    return node;
}

NodeML* newNodeML_info_next(MethodL *info, NodeML *next) {
    NodeML *node = newNodeML();
    node->info = info;
    node->next = next;
    return node;
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
