/********************************************************
*Define la estructura y funciones asociadas al manejo   *
*de pila de offset					                    *
********************************************************/

#ifndef STACKOFFSET_H
#define STACKOFFSET_H

#include "linknodeOffset.h"
#include <stdbool.h>

typedef struct {
    NodeStackOffset *top;
} StackOffset;

/**Constructor de la Pila de Offsets*/
StackOffset* newStackOffset();

/**Metodo que apila un Offset a la Pila*/
void pushOffset(StackOffset *stack, int offset);

/**Metodo para verificar si la Lista es Vacia*/
bool isEmptyOffset(StackOffset *stack);

/**Metodo que desapila un Offset en la Pila*/
int popOffset(StackOffset *stack);

/**Metodo que retorna el tope de la Pila sin desapilarlo*/
int peekOffset(StackOffset *stack);

#endif
