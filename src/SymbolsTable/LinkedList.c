/*
 * A implementation of linked list.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "string.h"

/* Returns an initialized linked list. */ 
LinkedList* initialize()
{
    LinkedList *l = (LinkedList*) malloc (sizeof(LinkedList));
    l->first = NULL;
    l->size = 0;
    return l;
}

/* Insert an element in the linked list "l". */
void insert(LinkedList *l, Attribute *attribute)
{
    Node *newNode;
    if ((newNode = (Node*) malloc(sizeof(Node)))) 
    {
        newNode->data = attribute;
        newNode->next = l->first;
        l->first = newNode;
        l->size++;
    }
    else 
        printf("LinkedList.c: insert ERROR: Can't reserve space in memory.");
}

/* Search the element "data" in the list "l" 
 *
 * Return Attribute* iff the attribute with id: "id" was found in the list.
 * Otherwise return NULL.
 * */
Attribute* search(LinkedList *l, char *id)
{
    Node *auxNode = l->first;
    int i;
    for (i = 0; i < l->size; i++)
    {
        if (strcmp(get_id(auxNode->data), id) == 0)
            return auxNode->data;
        auxNode = auxNode->next;
    }
    return NULL;
}

/* Return Attribute* of the last defined method in the list. Return NULL if there isn't a method defined */
Attribute* getLastDefinedMethod(LinkedList *l)
{
	Node *auxNode = l->first;
    int i;
    for (i = 0; i < l->size; i++)
    {
        if (auxNode->data->type == Method)
			return auxNode->data;
        auxNode = auxNode->next;
    }
    return NULL;
}

/* Delete all the elements of the list. */
void deleteAll(LinkedList *l)
{
    Node *aux;
    int i;
    for (i = 0; i < l->size; i++)
    {
        aux = l->first; 
        l->first = aux->next;
        free(aux);
    }
    l->first = NULL;
    l->size = 0;
}

/* Prints the variable info that contains attr */
void showVariableAttribute(Attribute *attr)
{
	printf(" type:.decl.variable:\n");
    switch (attr->decl.variable->type)
    {
        case Int:   printf("    int %s = %d;\n", get_id(attr), get_int_val(attr)); break;
        case Float: printf("    float %s = %f;\n", get_id(attr), get_float_val(attr)); break;
        case Bool:  printf("    boolean %s = %d;\n", get_id(attr), get_bool_val(attr)); break;
    }
}

/* Prints the method info that contains attr */
void showMethodAttribute(Attribute *attr)
{
	printf(" type:.decl.method\n");
    switch (attr->decl.method.type)
    {
        case RetInt:   printf("    int %s ();\n", get_id(attr)); break;
        case RetFloat: printf("    float %s ();\n", get_id(attr)); break;
        case RetBool:  printf("    boolean %s ();\n", get_id(attr)); break;
        case RetVoid:  printf("    void %s ();\n", get_id(attr)); break;
    }
}

/* Prints the array info that contains attr */
void showArrayAttribute(Attribute *attr)
{
    printf("    type:.decl.array\n");
    switch (attr->decl.array.type)
    {
        case Int:   printf("    int %s [%d];\n", get_id(attr), attr->decl.array.length); break;
        case Float: printf("    float %s [%d];\n", get_id(attr), attr->decl.array.length); break;
        case Bool:  printf("    boolean %s [%d];\n", get_id(attr), attr->decl.array.length); break;
    }
}

/* Print in display the elements of the list. */
void print_list(LinkedList *l)
{
    printf("\nLIST: \n\n");
    if (l->size == 0)
        printf("      empty...\n");
    Node *aux = l->first;
    int i;
    for (i = 0; i < l->size; i++)
    {
        switch (aux->data->type)
        {
            case Variable:  showVariableAttribute(aux->data); break;
            case Method:    showMethodAttribute(aux->data); break;
            case Array:     showArrayAttribute(aux->data); break;
        }
    }
}
