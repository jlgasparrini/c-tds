/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../ListMethod/genlistml.h"
#include "../code_3d/gencode3d.h"
#include "../Stack/stack.h"
#include "translate.h"

/* Initializes the assembly generator and writes it */
void InitAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* fileName);

#endif
