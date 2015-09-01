/*
* StringStack implementation.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StringStack.h"

/* Returns an initialized StringStack. */ 
StringStack* initialize_string_stack()
{
	StringStack *stack = (StringStack*) malloc (sizeof(StringStack));
	stack->first = NULL;
	stack->size = 0;
	return stack;
}

/* Insert an element in the stack "s". */
void push_string(StringStack *s, char *value)
{
	SNode *new_node = (SNode*) malloc (sizeof(SNode));
	if (new_node)
	{
		new_node->val = strdup(value);
		new_node->next = s->first;
		s->first = new_node;
		s->size++;
	}
	else 
		printf("StringStack.h: insert ERROR: Can't reserve space in memory.");
}

/* Return the value of the last pushed string in the stack "s". */
char* pop_string(StringStack *s)
{
	if (s->size > 0)
	{
		SNode *runner = s->first;
		char* auxVal = strdup(runner->val);
		s->first = runner->next;
		free(runner);
		s->size--;
		return auxVal;
	}
	return "";
}

/* Return the top string of the stack "s". */
char* top_string(StringStack *s)
{
	if (s->size > 0)
		return s->first->val;
	return "";
}

/* Prints the stack in the correct order */
void print_correct_order(StringStack *s)
{
	while (s->size > 0)
		printf("%s",pop_string(s));	
}

/* Prints the stack in the inverse order */
void print_inverse_order(StringStack *s)
{
	StringStack *aux = initialize_string_stack();
	while (s->size > 0)
		push_string(aux,pop_string(s));
	while (aux->size > 0)
	{
		printf("%s",top_string(aux));	
		push_string(s,pop_string(aux));
	}
}
