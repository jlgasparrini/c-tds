/********************************************************
*Implementacion de Node Link                           *
*********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linknode.h"

Label* newLabel(char *label, Attribute *eval) {
    Label *new = (Label*) malloc(sizeof(Label));
    new->label = label;
    new->eval = eval;
    return new;
}

NodeStack* newLinkNode_empty() {
    NodeStack *new = (NodeStack*) malloc(sizeof(NodeStack));
    new->info = NULL;
    new->next = NULL;
    return new;
}

NodeStack* newLinkNode_info(char *info, Attribute *eval){
    NodeStack *new = newLinkNode_empty();
    new->info = newLabel(info, eval);
    return new;
}

NodeStack* newLinkNode_info_next(char *info, Attribute *eval, NodeStack *next) {
    NodeStack *new = newLinkNode_info(info, eval);
    new->next = next;
    return new;
}

Label* getInfo_linkNode(NodeStack *node) {
    return node->info;
}

NodeStack* getNext_linkNode(NodeStack *node) {
    return node->next;
}

void setInfo_linkNode(NodeStack *node, char *info, Attribute *eval) {
    node->info = newLabel(info, eval);
}

void setNext_linkNode(NodeStack *node, NodeStack *next) {
    node->next = next;
}
