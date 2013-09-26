/*
 * A implementation of linked list.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

/* Returns an initialized linked list. */ 
LinkedList* initialize()
{
    LinkedList *l = (LinkedList*) malloc (sizeof(LinkedList));
    (*l).first = NULL;
    (*l).size = 0;
    return l;
}

/* Insert an element in the linked list "l". */
void insert(LinkedList *l, Attribute *attribute)
{
    Node *newNode;
    if (newNode = (Node*) malloc(sizeof(Node))) 
    {
        (*newNode).data = attribute;
        (*newNode).next = (*l).first;
        (*l).first = newNode;
        (*l).size++;
    }
    else 
    {
        printf("LinkedList.c: insert ERROR: Can't reserve space in memory.");
    }
}

/* Search the element "data" in the list "l" 
 *
 * Return Attribute* iff the attribute with id: "id" was found in the list.
 * Otherwise return NULL.
 * */
Attribute* search(LinkedList *l, char *id)
{
    Node *auxNode = (*l).first;
    int i;
    for (i = 0; i < (*l).size; i++)
    {
        if ((*(*auxNode).data).type == Variable)
            if (strcmp((*(*auxNode).data).decl.variable.id, id) == 0)
                return (*auxNode).data;
        if ((*(*auxNode).data).type == Method)
            if (strcmp((*(*auxNode).data).decl.method.id, id) == 0)
                return (*auxNode).data;
        if ((*(*auxNode).data).type == Array)
            if (strcmp((*(*auxNode).data).decl.array.id, id) == 0)
                return (*auxNode).data;
        auxNode = (*auxNode).next;
    }
    return NULL;
}

/* Return Attribute* of the last defined method in the list. Return NULL if there isn't a method defined */
Attribute* getLastDefinedMethod(LinkedList *l)
{
	Attribute *auxAttr = NULL;
	Node *auxNode = (*l).first;
    int i;
    for (i = 0; i < (*l).size; i++)
    {
        if ((*(*auxNode).data).type == Method)
			return (*auxNode).data;
        auxNode = (*auxNode).next;
    }
    return NULL;
}

/* Delete all the elements of the list. */
void deleteAll(LinkedList *l)
{
    Node *aux;
    int i = 0;
    while (i < (*l).size)
    {
        aux = (*l).first; 
        (*l).first = (*aux).next;
       // free((*aux).data);
        free(aux);
        i++;
    }
    (*l).first = NULL;
    (*l).size = 0;
}

/* Prints the variable info that contains attr */
void showVariableAttribute(Attribute *attr)
{
	printf(" type:.decl.variable:\n");
    if ((*attr).decl.variable.type == Int)
        printf("    int %s = %d;\n", (*attr).decl.variable.id, (*attr).decl.variable.value.intVal);
    if ((*attr).decl.variable.type == Float)
        printf("    float %s = %f;\n", (*attr).decl.variable.id, (*attr).decl.variable.value.floatVal);
    if ((*attr).decl.variable.type == Bool)
        printf("    boolean %s = %d;\n", (*attr).decl.variable.id, (*attr).decl.variable.value.boolVal);
}

/* Prints the method info that contains attr */
void showMethodAttribute(Attribute *attr)
{
	printf(" type:.decl.method\n");
	if ((*attr).decl.method.type == RetInt)
	    printf("    int %s ();\n", (*attr).decl.method.id);
	if ((*attr).decl.method.type == RetFloat)
	    printf("    float %s ();\n", (*attr).decl.method.id);
	if ((*attr).decl.method.type == RetBool)
	    printf("    boolean %s ();\n", (*attr).decl.method.id);
	if ((*attr).decl.method.type == RetVoid)
	    printf("    void %s ();\n", (*attr).decl.method.id);
}

/* Prints the array info that contains attr */
void showArrayAttribute(Attribute *attr)
{
	printf("    type:.decl.array\n");
	if ((*attr).decl.array.type == Int)
	    printf("    int %s [%d];\n", (*attr).decl.array.id, (*attr).decl.array.length);
	if ((*attr).decl.variable.type == Float)
	    printf("    float %s [%d];\n", (*attr).decl.array.id, (*attr).decl.array.length);
	if ((*attr).decl.variable.type == Bool)
	    printf("    boolean %s [%d];\n", (*attr).decl.array.id, (*attr).decl.array.length);
}

/* Print in display the elements of the list. */
void print_list(LinkedList *l)
{
    printf("\nLIST: \n\n");
    Node *aux = (*l).first;
    int i = 0;
    if ((*l).size == 0)
        printf("      empty...\n");
    while (i < (*l).size) 
    {
        if ((*(*aux).data).type == Variable)
			showVariableAttribute((*aux).data);
        if ((*(*aux).data).type == Method)
			showMethodAttribute((*aux).data);
        if ((*(*aux).data).type == Array)
			showArrayAttribute((*aux).data);
		aux = (*aux).next;
        i++;
    }
}
