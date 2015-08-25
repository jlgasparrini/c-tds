/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linknodeOffset.h"

/**Constructor de un Nodo de la Pila vacio*/
NodeStackOffset* newLinkNodeOffset()
{
  NodeStackOffset *node = (NodeStackOffset*) malloc(sizeof(NodeStackOffset));
  node->info = NULL;
  node->next = NULL;
  return node;
}

/**Constructor de un Nodo de la Pila con el campo info*/
NodeStackOffset* newLinkNodeOffset_info(int info)
{
  NodeStackOffset *node = newLinkNodeOffset();
  node->info = &info;
  return node;
}

/**Constructor de un Nodo de la Pila con los campos info y next*/
NodeStackOffset* newLinkNodeOffset_info_next(int info, NodeStackOffset *next)
{
  NodeStackOffset *node = newLinkNodeOffset();
  node->info = &info;
  node->next = next;
  return node;
}

/**Metodo que retorna el campo info de un nodo dado*/
int getInfo_linkNodeOffset(NodeStackOffset *node)
{
  return *node->info;
}

/**Metodo que retorna el campo next de un nodo dado*/
NodeStackOffset* getNext_linkNodeOffset(NodeStackOffset *node)
{
  return node->next;
}

/**Metodo que setea el campo info de un nodo dado*/
void setInfo_linkNodeOffset(NodeStackOffset *node, int info)
{
  node->info = &info;
}

/**Metodo que setea el campo next de un nodo dado*/
void setNext_linkNodeOffset(NodeStackOffset *node, NodeStackOffset *next)
{
  node->next = next;
}
