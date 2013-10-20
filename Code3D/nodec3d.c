/********************************************************
*Implementacion de NodoC3D                              *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodec3d.h"

NodeC3D* newNodeC3D_empty() {
    NodeC3D *new = (NodeC3D*) malloc(sizeof(NodeC3D));
    (*new).info = NULL;
    (*new).next = NULL;
    return new;
}

NodeC3D* newNodeC3D_info(Code3D *info) {
    NodeC3D *new = newNodeC3D_empty();
    (*new).info = info;
    return new;
}

NodeC3D* newNodeC3D_info_next(Code3D *info, NodeC3D *next) {
    NodeC3D *new = newNodeC3D_info(info);
    (*new).next = next;
    return new;
}

Code3D* getInfo_nodeC3D(NodeC3D *node) {
    return (*node).info;
}

NodeC3D* getNext_NodeC3D(NodeC3D *node) {
    return (*node).next;
}

void setInfo_nodeC3D(NodeC3D *node, Code3D *info) {
    (*node).info = info;
}

void setNext_nodeC3D(NodeC3D *node, NodeC3D *next) {
    (*node).next = next;
}
