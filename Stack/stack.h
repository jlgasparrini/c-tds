/********************************************************
*Define la estructura y funciones asociadas al manejo   *
*de pila de cadenas de caracteres                       *
********************************************************/

#ifndef STACK_H
#define STACK_H

#include "linknode.h"
#include <stdbool.h>

typedef struct {
    NodeStack *top;
} Stack;

/**Constructor de la Pila de Labels*/
Stack* newStack();

/**Metodo que apila un Label a la Pila*/
void push(Stack *stack, char *label);

/**Metodo para verificar si la Lista es Vacia*/
bool isEmpty(Stack *stack);

/**Metodo que desapila un Label a la Pila*/
char* pop(Stack *stack);

/**Metodo que retorna el tope de la Pila sin desapilarlo*/
char* peek(Stack *stack);

#endif
