/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "translate.h"
#include "../code_3d/gencode3d.h"

/* Initializes the assembly generator and writes it */
void init_assembler(ListMLabel*, LCode3D*, char*);

#endif
