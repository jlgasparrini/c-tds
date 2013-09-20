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

/* Delete an element of the list. */
void delete(LinkedList *l, char *id)
{
    Attribute *auxAttr = search(l, id);
    if ((*l).size > 0 && auxAttr != NULL)
    {
        Node *aux = (*l).first;
        Node *previous = aux;
        int i = 0;
        int flag = 0; //True
        while (i < (*l).size && flag == 0)
        {
            if ((*(*aux).data).type == Variable)
            {
                if (strcmp(id, (*(*aux).data).decl.variable.id) == 0)
                    flag = 1;
            }
            if ((*(*aux).data).type == Method)
           {
                if (strcmp(id, (*(*aux).data).decl.method.id) == 0)
                    flag = 1;
            }
            if ((*(*aux).data).type == Array)
            {
                if (strcmp(id, (*(*aux).data).decl.array.id) == 0)
                    flag = 1;
            }
            if (flag != 1) //Item not found.
            {
                previous=aux;
                aux = (*aux).next;
                i++;
            }
            else //Item found.
            {
                (*previous).next = (*aux).next;
                (*l).size--;
                if (i == 0)
                {
                    aux = (*l).first;
                    (*l).first = (*(*l).first).next;    
                }
               //free((*aux).data);
                free(aux);
            }
        }
    }
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
        if ((*(*aux).data).type != Variable && (*(*aux).data).type != Method && (*(*aux).data).type != Array)
            printf("\n\nESTO NO DEBERIA DE PASAR JAMAS!!!!!!!!!\n\n");
        if ((*(*aux).data).type == Variable)
        {
            printf(" .decl.variable:\n");
            if ((*(*aux).data).decl.variable.type == Int)
                printf("    int %s = %d;\n\n", (*(*aux).data).decl.variable.id, (*(*aux).data).decl.variable.value.intVal);
            if ((*(*aux).data).decl.variable.type == Float)
                printf("    float %s = %f;\n\n", (*(*aux).data).decl.variable.id, (*(*aux).data).decl.variable.value.floatVal);
            if ((*(*aux).data).decl.variable.type == Bool)
                printf("    boolean %s = %d;\n\n", (*(*aux).data).decl.variable.id, (*(*aux).data).decl.variable.value.boolVal);
        }
       
        if ((*(*aux).data).type == Method)
        {
            printf(" type:.decl.method\n");
            printf(" id: %s\n", (*(*aux).data).decl.method.id);
            if ((*(*aux).data).decl.method.type == RetInt)
                printf("    int %s ();\n\n", (*(*aux).data).decl.method.id);
            if ((*(*aux).data).decl.method.type == RetFloat)
                printf("    float %s ();\n\n", (*(*aux).data).decl.method.id);
            if ((*(*aux).data).decl.method.type == RetBool)
                printf("    boolean %s ();\n\n", (*(*aux).data).decl.method.id);
            if ((*(*aux).data).decl.method.type == RetVoid)
                printf("    void %s ();\n\n", (*(*aux).data).decl.method.id);
        }

        if ((*(*aux).data).type == Array)
        {
            printf("    type:.decl.array\n");
            printf("    id: %s\n", (*(*aux).data).decl.array.id);
            if ((*(*aux).data).decl.array.type == Int)
                printf("    int %s [%d];\n\n", (*(*aux).data).decl.array.id, (*(*aux).data).decl.array.length);
            if ((*(*aux).data).decl.variable.type == Float)
                printf("    float %s [%d];\n\n", (*(*aux).data).decl.array.id, (*(*aux).data).decl.array.length);
            if ((*(*aux).data).decl.variable.type == Bool)
                printf("    boolean %s [%d];\n\n", (*(*aux).data).decl.array.id, (*(*aux).data).decl.array.length);
        }
        aux = (*aux).next;
        i++;
    }
}
