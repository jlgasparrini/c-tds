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
	LinkedList *list = (LinkedList*) malloc (sizeof(LinkedList));
	list->first = NULL;
	list->size = 0;
	return list;
}

/* Insert an element in the linked list "l". */
void insert(LinkedList *list, Attribute *attribute)
{
	Node *new_node;
	if ((new_node = (Node*) malloc(sizeof(Node)))) 
	{
		new_node->data = attribute;
		new_node->next = list->first;
		list->first = new_node;
		list->size++;
	}
	else 
		printf("LinkedList.c: insert ERROR: Can't reserve space in memory.");
}

/* Search the element "data" in the list "l" 
*
* Return Attribute* iff the attribute with id: "id" was found in the list.
* Otherwise return NULL.
* */
Attribute* search(LinkedList *list, char *id)
{
	Node *runner = list->first;
	int i;
	for (i = 0; i < list->size; i++)
	{
		if (strcmp(get_id(runner->data), id) == 0)
			return runner->data;
		runner = runner->next;
	}
	return NULL;
}

/* Return Attribute* of the last defined method in the list. Return NULL if there isn't a method defined */
Attribute* get_last_defined_method(LinkedList *list)
{
	Node *runner = list->first;
	int i;
	for (i = 0; i < list->size; i++)
	{
		if (runner->data->type == Method)
			return runner->data;
		runner = runner->next;
	}
	return NULL;
}

/* Delete all the elements of the list. */
void delete_all(LinkedList *list)
{
	Node *runner;
	int i;
	for (i = 0; i < list->size; i++)
	{
		runner = list->first; 
		list->first = runner->next;
		free(runner);
	}
	list->first = NULL;
	list->size = 0;
}

/* Prints the variable info that contains attr */
void show_variable_attribute(Attribute *attr)
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
void show_method_attribute(Attribute *attr)
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
void show_array_attribute(Attribute *attr)
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
void print_list(LinkedList *list)
{
	printf("\nLIST: \n\n");
	if (list->size == 0)
		printf("      empty...\n");
	Node *runner = list->first;
	int i;
	for (i = 0; i < list->size; i++)
	{
		switch (runner->data->type)
		{
			case Variable:  show_variable_attribute(runner->data); break;
			case Method:    show_method_attribute(runner->data); break;
			case Array:     show_array_attribute(runner->data); break;
		}
	}
}
