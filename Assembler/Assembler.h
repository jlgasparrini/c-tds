
/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../ListMethod/genlistml.h"
#include "../Code3D/gencode3d.h"

/* Initializes the interpreter and runs it */
void initAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack);

#endif
