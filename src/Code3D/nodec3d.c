/********************************************************
*Implementacion de NodoC3D                              *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodec3d.h"

/**Constructor de un Nodo vacio*/
NodeC3D* newNodeC3D_empty() {
    NodeC3D *new = (NodeC3D*) malloc(sizeof(NodeC3D));
    (*new).info = NULL;
    (*new).next = NULL;
    return new;
}

/**Constructor de un Nodo con el campo info*/
NodeC3D* newNodeC3D_info(Code3D *info) {
    NodeC3D *new = newNodeC3D_empty();
    (*new).info = info;
    return new;
}

/**Constructor de un Nodo con el campo info y next*/
NodeC3D* newNodeC3D_info_next(Code3D *info, NodeC3D *next) {
    NodeC3D *new = newNodeC3D_info(info);
    (*new).next = next;
    return new;
}

/**Metodo que retorna el campo info(Codigo 3D) de un Nodo*/
Code3D* getInfo_nodeC3D(NodeC3D *node) {
    return (*node).info;
}

/**Metodo que retorna el campo next de un Nodo*/
NodeC3D* getNext_NodeC3D(NodeC3D *node) {
    return (*node).next;
}

/**Metodo que setea el campo info(Codigo 3D) de un Nodo*/
void setInfo_nodeC3D(NodeC3D *node, Code3D *info) {
    (*node).info = info;
}

/**Metodo que setea el campo next de un Nodo*/
void setNext_nodeC3D(NodeC3D *node, NodeC3D *next) {
    (*node).next = next;
}