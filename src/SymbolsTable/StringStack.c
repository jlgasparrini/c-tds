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

/* Insert an element in the stack "stack". */
void push_string(StringStack *stack, char *value)
{
	SNode *new_node = (SNode*) malloc (sizeof(SNode));
	if (new_node)
	{
		new_node->val = strdup(value);
		new_node->next = stack->first;
		stack->first = new_node;
		stack->size++;
	}
	else 
		printf("StringStack.h: insert ERROR: Can't reserve space in memory.");
}

/* Return the value of the last pushed string in the stack "stack". */
char* pop_string(StringStack *stack)
{
	if (stack->size > 0)
	{
		SNode *runner = stack->first;
		char* auxVal = strdup(runner->val);
		stack->first = runner->next;
		free(runner);
		stack->size--;
		return auxVal;
	}
	return "";
}

/* Return the top string of the stack "stack". */
char* top_string(StringStack *stack)
{
	if (stack->size > 0)
		return stack->first->val;
	return "";
}

/* Prints the stack in the correct order */
void print_correct_order(StringStack *stack)
{
	while (stack->size > 0)
		printf("%stack",pop_string(stack));	
}

/* Prints the stack in the inverse order */
void print_inverse_order(StringStack *stack)
{
	StringStack *aux = initialize_string_stack();
	while (stack->size > 0)
		push_string(aux,pop_string(stack));
	while (aux->size > 0)
	{
		printf("%stack",top_string(aux));	
		push_string(stack,pop_string(aux));
	}
}
