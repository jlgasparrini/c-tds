
/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../ListMethod/genlistml.h"
#include "../Code3D/gencode3d.h"
#include "../Stack/stack.h"
#include "Translate.h"

/* Initializes the interpreter and runs it */
void InitAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* fileName);

#endif