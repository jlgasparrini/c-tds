/********************************************************
*Implementacion de pila de offset				        *
*********************************************************/
#include "stackOffset.h"
#include <stdlib.h>

/**Constructor de la Pila de Offsets*/
StackOffset* new_stack_offset()
{
	StackOffset *stack = (StackOffset*) malloc(sizeof(StackOffset));
	stack->top = NULL;
	return stack;
}

/**Metodo que apila un Offset a la Pila*/
void push_offset(StackOffset *stack, int offset)
{
	NodeStackOffset *st = new_link_node_offset_info_next(offset, stack->top);
	stack->top = st;
}

/**Metodo para verificar si la Lista es Vacia*/
bool is_empty_offset(StackOffset *stack)
{
	return stack->top == NULL;
}

/**Metodo que desapila un Offset en la Pila*/
int pop_offset(StackOffset *stack)
{
	int ret = get_info_link_node_offset(stack->top);
	stack->top = get_next_link_node_offset(stack->top);
	return ret;
}

/**Metodo que retorna el tope de la Pila sin desapilarlo*/
int peek_offset(StackOffset *stack)
{
	return get_info_link_node_offset(stack->top);
}
