/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linknodeOffset.h"

/**Constructor de un Nodo de la Pila vacio*/
NodeStackOffset* new_link_node_offset()
{
  NodeStackOffset *node = (NodeStackOffset*) malloc(sizeof(NodeStackOffset));
  node->info = NULL;
  node->next = NULL;
  return node;
}

/**Constructor de un Nodo de la Pila con el campo info*/
NodeStackOffset* new_link_node_offset_info(int info)
{
  NodeStackOffset *node = new_link_node_offset();
  node->info = &info;
  return node;
}

/**Constructor de un Nodo de la Pila con los campos info y next*/
NodeStackOffset* new_link_node_offset_info_next(int info, NodeStackOffset *next)
{
  NodeStackOffset *node = new_link_node_offset();
  node->info = &info;
  node->next = next;
  return node;
}

/**Metodo que retorna el campo info de un nodo dado*/
int get_info_link_node_offset(NodeStackOffset *node)
{
  return *node->info;
}

/**Metodo que retorna el campo next de un nodo dado*/
NodeStackOffset* get_next_link_node_offset(NodeStackOffset *node)
{
  return node->next;
}

/**Metodo que setea el campo info de un nodo dado*/
void set_info_link_node_offset(NodeStackOffset *node, int info)
{
  node->info = &info;
}

/**Metodo que setea el campo next de un nodo dado*/
void set_next_link_node_offset(NodeStackOffset *node, NodeStackOffset *next)
{
  node->next = next;
}
