/********************************************************
*Implementacion de pila de cadenas de caracteres        *
*********************************************************/
#include "stack.h"
#include <stdlib.h>

/**Constructor de la Pila de Labels*/
Stack* newStack() 
{
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

/**Metodo que apila un Label a la Pila*/
void push(Stack *stack, char *label) 
{
    NodeStack *node = newLinkNode_info_next(label, stack->top);
    stack->top = node;
}

/**Metodo para verificar si la Lista es Vacia*/
bool isEmpty(Stack *stack) 
{
    return stack->top == NULL;
}

/**Metodo que desapila un Label a la Pila*/
char* pop(Stack *stack) 
{
    char *ret = getInfo_linkNode(stack->top);
    stack->top = getNext_linkNode(stack->top);
    return ret;
}

/**Metodo que retorna el tope de la Pila sin desapilarlo*/
char* peek(Stack *stack) 
{
    return getInfo_linkNode(stack->top);
}
