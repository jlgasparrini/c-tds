/********************************************************
*Implementacion de pila de cadenas de caracteres        *
*********************************************************/
    #include "stack.h"
#include <stdlib.h>

Stack* newStack() 
{
    Stack *new = (Stack*) malloc(sizeof(Stack));
    new->top = NULL;
    return new;
}

void push(Stack *stack, char *label) 
{
    //printf(" apileeee %s \n", label);
    NodeStack *new = newLinkNode_info_next(label, stack->top);
    stack->top = new;
}

bool isEmpty(Stack *stack) 
{
    return stack->top == NULL;
}

char* pop(Stack *stack) 
{
    char *ret = getInfo_linkNode(stack->top);
    //printf(" desapileee %s \n", ret);
    stack->top = getNext_linkNode(stack->top);
    return ret;
}

char* peek(Stack *stack) 
{
    char *ret = getInfo_linkNode(stack->top);
    return ret;
}
