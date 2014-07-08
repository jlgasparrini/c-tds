/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "translate.h"
#include "../code_3d/gencode3d.h"
#include "../stack/stack.h"

/* Initializes the assembly generator and writes it */
void InitAssembler(ListMLabel*, LCode3D*, Stack*, char*);

#endif
