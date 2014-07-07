/*
 * Interprete
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../ListMethod/genlistml.h"
#include "../code_3d/gencode3d.h"

/* Initializes the interpreter and runs it */
void InitInterpreter(ListMLabel *labelL, LCode3D *codeL);

#endif
