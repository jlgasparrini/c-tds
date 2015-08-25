/*
 * StringStack implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StringStack.h"

/* Returns an initialized StringStack. */ 
StringStack* initializeSS()
{
    StringStack *stack = (StringStack*) malloc (sizeof(StringStack));
    stack->first = NULL;
    stack->size = 0;
    return stack;
}

/* Insert an element in the stack "s". */
void pushString(StringStack *s, char *value)
{
    SNode *newNode = (SNode*) malloc (sizeof(SNode));
    if (newNode)
    {
        newNode->val = strdup(value);
        newNode->next = s->first;
        s->first = newNode;
        s->size++;
    }
    else 
        printf("StringStack.h: insert ERROR: Can't reserve space in memory.");
}

/* Return the value of the last pushed string in the stack "s". */
char* popString(StringStack *s)
{
    if (s->size > 0)
    {
        SNode *auxNode = s->first;
        char* auxVal = strdup(auxNode->val);
		s->first = auxNode->next;
        free(auxNode);
		s->size--;
        return auxVal;
    }
    return "";
}

/* Return the top string of the stack "s". */
char* topString(StringStack *s)
{
    if (s->size > 0)
        return s->first->val;
    return "";
}

/* Prints the stack in the correct order */
void printCorrectOrder(StringStack *s)
{
	while (s->size > 0)
		printf("%s",popString(s));	
}

/* Prints the stack in the inverse order */
void printInverseOrder(StringStack *s)
{
	StringStack *aux = initializeSS();
	while (s->size > 0)
		pushString(aux,popString(s));
	while (aux->size > 0)
	{
		printf("%s",topString(aux));	
		pushString(s,popString(aux));
	}
}
