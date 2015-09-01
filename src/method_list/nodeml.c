/********************************************************
*Implementacion de NodeML                              	*
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "nodeml.h"

NodeML* new_node_ml() {
	NodeML *node = (NodeML*) malloc(sizeof(NodeML));
	node->info = NULL;
	node->next = NULL;
	return node;
}

NodeML* new_node_ml_info(MethodL *info) {
	NodeML *node = new_node_ml();
	node->info = info;
	return node;
}

NodeML* new_node_ml_info_next(MethodL *info, NodeML *next) {
	NodeML *node = new_node_ml();
	node->info = info;
	node->next = next;
	return node;
}

MethodL* get_info_node_ml(NodeML *node) {
	return node->info;
}

NodeML* get_next_node_ml(NodeML *node) {
	return node->next;
}

void set_info_node_ml(NodeML *node, MethodL *info) {
	node->info = info;
}

void set_next_node_ml(NodeML *node, NodeML *next) {
	node->next = next;
}
