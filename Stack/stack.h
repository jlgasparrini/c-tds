/********************************************************
*Define la estructura y funciones asociadas al manejo   *
*de pila de cadenas de caracteres                       *
********************************************************/

#ifndef STACK_H
#define STACK_H

#include "linknode.h"
#include "label.h"
#include <stdbool.h>

typedef struct {
    NodeStack *top;
} Stack;

Stack* newStack();

void push(Stack *stack, char *label);

bool isEmpty(Stack *stack);

Label* pop(Stack *stack);

Label* peek(Stack *stack);

#endif
