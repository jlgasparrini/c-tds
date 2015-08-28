/*
 * A linked list header.
 */
 
#ifndef LinkedList_H
#define LinkedList_H

#include "Attribute.h"

/* Node of the linked list. */
typedef struct N 
{
    Attribute *data;
    /* Pointer of the next node. */
    struct N *next;
} Node;
 
/* Define type LinkedList. */
typedef struct
{
    /* Pointer to first nodes of my list. */
    Node *first;
    /* Size of the list. */
    int size;
} LinkedList;

/* Returns an initialized linked list. */ 
LinkedList* initialize();

/* Insert an element in the linked list "l". */
void insert(LinkedList *l, Attribute *attribute);
 
/* Search the element "data" in the list "l" */
Attribute* search(LinkedList *l, char *id);

/* Return Attribute* of the last defined method in the list. */
Attribute* get_last_defined_method(LinkedList *l);

/* Delete all the elements of the list. */
void delete_all(LinkedList *l);

/* Print in display the elements of the list. */
void print_list(LinkedList *l);

#endif
