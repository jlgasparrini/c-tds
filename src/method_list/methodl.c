/**********************************************************************
*Implementacion Codigo de 3 Direcciones                               *
**********************************************************************/

#include "methodl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MethodL* new_method_l(char *id_method, char *label_method)
{
    MethodL *ml = (MethodL*) malloc(sizeof(MethodL));
	ml->id = strdup(id_method);
    ml->label = strdup(label_method);
    return ml;
}

char* get_id_method(MethodL *methodl) {
    return methodl->id;
}

char* get_label_method(MethodL *methodl) {
    return methodl->label;
}

void set_id_method(MethodL *methodl, char *id_method){
    methodl->id = strdup(id_method);
}

void set_label_method(MethodL *methodl, char *label_method){
    methodl->label = strdup(label_method);
}

void to_string_method_l(MethodL *methodl) {
    printf("Id del metodo %s \n", get_id_method(methodl));
    printf("Label del metodo %s \n", get_label_method(methodl));
}


