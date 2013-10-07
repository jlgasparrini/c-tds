/************************************************************
*Define una estructura que contiene un label y una variable *
*la cual se usa al evaluar saltos condicionales             *
*************************************************************/

#ifndef LABEL_H
#define LABEL_H

#include "../SymbolsTable/Attribute.h"

typedef struct {
    char *label;
    Attribute *eval;
} Label;

#endif