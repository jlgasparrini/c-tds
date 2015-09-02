/********************************************************
*Implementacion de NodoC3D                              *
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodec3d.h"

/**Constructor de un Nodo vacio*/
NodeC3D* new_node_c3d() {
	NodeC3D *node = (NodeC3D*) malloc(sizeof(NodeC3D));
	node->info = NULL;
	node->next = NULL;
	return node;
}

/**Constructor de un Nodo con el campo info*/
NodeC3D* new_node_c3d_info(Code3D *info) {
	NodeC3D *node = new_node_c3d();
	node->info = info;
	return node;
}

/**Constructor de un Nodo con el campo info y next*/
NodeC3D* new_node_c3d_info_next(Code3D *info, NodeC3D *next) {
	NodeC3D *node = new_node_c3d();
	node->info = info;
	node->next = next;
	return node;
}

/**Metodo que retorna el campo info(Codigo 3D) de un Nodo*/
Code3D* get_info_node_c3d(NodeC3D *node) {
	return node->info;
}

/**Metodo que retorna el campo next de un Nodo*/
NodeC3D* get_next_node_c3d(NodeC3D *node) {
	return node->next;
}

/**Metodo que setea el campo info(Codigo 3D) de un Nodo*/
void set_info_node_c3d(NodeC3D *node, Code3D *info) {
	node->info = info;
}

/**Metodo que setea el campo next de un Nodo*/
void set_next_node_c3d(NodeC3D *node, NodeC3D *next) {
	node->next = next;
}
