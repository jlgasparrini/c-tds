/**********************************************************************
*Implementacion Codigo de 3 Direcciones                               *
**********************************************************************/

#include "methodl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MethodL* newMethodL(char *id_method, char *label_method);
 {
    MethodL *new = (MethodL*) malloc(sizeof(MethodL));
	new->id = malloc(strlen(id_method) + 1);
    new->label = malloc(strlen(label_method) + 1);
	strcpy(new->id, id_method);
	strcpy(new->label, label_method);
    return new;
}

char* getIdMethod(MethodL *methodl) {
    return methodl->id;
}

char* getLabelMethod(MethodL *methodl) {
    return methodl->label;
}

void setIdMethod(MethodL *methodl, char *id_method){
        methodl->id = malloc(strlen(id_method) + 1);
        strcpy(methodl->id, id_method);    
}

void setLabelMethod(MethodL *methodl, char *label_method){
        methodl->label = malloc(strlen(label_method) + 1);
        strcpy(methodl->label, label_method);    
}

void toStringMethodL(MethodL *methodl) {
    printf("Id del metodo %s \n", getIdMethod(methodl));
    printf("Label del metodo %s \n", getLabelMethod(methodl));
}


