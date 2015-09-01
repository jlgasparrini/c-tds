/*
 * Interprete
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../method_list/genlistml.h"
#include "../code_3d/gencode3d.h"

/* Initializes the interpreter and runs it */
void init_interpreter(ListMLabel *label_l, ListC3D *code_l);

#endif
