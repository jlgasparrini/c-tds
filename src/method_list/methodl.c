/**********************************************************************
*Implementacion Codigo de 3 Direcciones                               *
***********************************************************************/

#include "methodl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MethodL* new_method_l(char *id_method, char *label_method)
{
	MethodL *method_l = (MethodL*) malloc(sizeof(MethodL));
	method_l->id = strdup(id_method);
	method_l->label = strdup(label_method);
	return method_l;
}

char* get_id_method(MethodL *method_l) {
	return method_l->id;
}

char* get_label_method(MethodL *method_l) {
	return method_l->label;
}

void set_id_method(MethodL *method_l, char *id_method){
	method_l->id = strdup(id_method);
}

void set_label_method(MethodL *method_l, char *label_method){
	method_l->label = strdup(label_method);
}

void to_string_method_l(MethodL *method_l) {
	printf("Id del metodo %s \n", get_id_method(method_l));
	printf("Label del metodo %s \n", get_label_method(method_l));
}


