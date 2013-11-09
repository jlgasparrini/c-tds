/********************************************************
*Implementacion de pila de offset				        *
*********************************************************/
#include "stackOffset.h"
#include <stdlib.h>

/**Constructor de la Pila de Offsets*/
StackOffset* newStackOffset() 
{
    StackOffset *new = (StackOffset*) malloc(sizeof(StackOffset));
    new->top = NULL;
    return new;
}

/**Metodo que apila un Offset a la Pila*/
void pushOffset(StackOffset *stack, int offset) 
{
    NodeStackOffset *new = newLinkNode_info_next(label, stack->top);
    stack->top = new;
}

/**Metodo para verificar si la Lista es Vacia*/
bool isEmptyOffset(StackOffset *stack) 
{
    return stack->top == NULL;
}

/**Metodo que desapila un Offset en la Pila*/
int popOffset(StackOffset *stack) 
{
    int ret = getInfo_linkNode(stack->top);
    stack->top = getNext_linkNode(stack->top);
    return ret;
}

/**Metodo que retorna el tope de la Pila sin desapilarlo*/
int peekOffset(StackOffset *stack) 
{
    int ret = getInfo_linkNode(stack->top);
    return ret;
}
