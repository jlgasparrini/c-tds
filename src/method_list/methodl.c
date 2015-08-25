/**********************************************************************
*Implementacion Codigo de 3 Direcciones                               *
**********************************************************************/

#include "methodl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MethodL* newMethodL(char *id_method, char *label_method)
{
    MethodL *ml = (MethodL*) malloc(sizeof(MethodL));
	ml->id = strdup(id_method);
    ml->label = strdup(label_method);
    return ml;
}

char* getIdMethod(MethodL *methodl) {
    return methodl->id;
}

char* getLabelMethod(MethodL *methodl) {
    return methodl->label;
}

void setIdMethod(MethodL *methodl, char *id_method){
    methodl->id = strdup(id_method);
}

void setLabelMethod(MethodL *methodl, char *label_method){
    methodl->label = strdup(label_method);
}

void toStringMethodL(MethodL *methodl) {
    printf("Id del metodo %s \n", getIdMethod(methodl));
    printf("Label del metodo %s \n", getLabelMethod(methodl));
}


