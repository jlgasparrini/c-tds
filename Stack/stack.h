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

Stack* newStack();

void push(Stack *stack, char *label);

bool isEmpty(Stack *stack);

char* pop(Stack *stack);

char* peek(Stack *stack);

#endif
