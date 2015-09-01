/*
 * Assembly Code Generator
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "translate.h"
#include "../code_3d/gencode3d.h"

/* Initializes the assembly generator and writes it */
void init_assembler(ListMLabel *ext_label_list, ListC3D *ext_code_list, char* name_of_file);

#endif
