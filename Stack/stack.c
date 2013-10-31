/********************************************************
*Implementacion de pila de cadenas de caracteres        *
*********************************************************/
#include "stack.h"
#include <stdlib.h>

/**Constructor de la Pila de Labels*/
Stack* newStack() 
{
    Stack *new = (Stack*) malloc(sizeof(Stack));
    new->top = NULL;
    return new;
}

/**Metodo que apila un Label a la Pila*/
void push(Stack *stack, char *label) 
{
    NodeStack *new = newLinkNode_info_next(label, stack->top);
    stack->top = new;
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
    char *ret = getInfo_linkNode(stack->top);
    return ret;
}
