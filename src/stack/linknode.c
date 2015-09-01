/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linknode.h"

/**Constructor de un Nodo de la Pila vacio*/
NodeStack* new_link_node() 
{
	NodeStack *node = (NodeStack*) malloc(sizeof(NodeStack));
	node->info = NULL;
	node->next = NULL;
	return node;
}

/**Constructor de un Nodo de la Pila con el campo info*/
NodeStack* new_link_node_info(char *info)
{
	NodeStack *node = new_link_node();
	node->info = strdup(info);
	return node;
}

/**Constructor de un Nodo de la Pila con los campos info y next*/
NodeStack* new_link_node_info_next(char *info, NodeStack *next) 
{
	NodeStack *node = new_link_node();
	node->info = strdup(info);
	node->next = next;
	return node;
}

/**Metodo que retorna el campo info de un nodo dado*/
char* get_info_link_node(NodeStack *node) 
{
	return node->info;
}

/**Metodo que retorna el campo next de un nodo dado*/
NodeStack* get_next_link_node(NodeStack *node) 
{
	return node->next;
}

/**Metodo que setea el campo info de un nodo dado*/
void set_info_link_node(NodeStack *node, char *info) 
{
	node->info = strdup(info);
}

/**Metodo que setea el campo next de un nodo dado*/
void set_next_link_node(NodeStack *node, NodeStack *next) 
{
	node->next = next;
}
