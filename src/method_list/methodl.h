/**************************************************
*Define la estructura de el lebal de un metodo    *
*                                                 *
*Una label va a tener :                           *
* id	   	 :   identificador del metodo 		  		*
* label      :   label del metodo		          		*
**************************************************/

#ifndef methodl_H
#define methodl_H

#include <stdbool.h>

typedef struct {
	char *id;
	char *label;
} MethodL;


/**Constructor de un Codigo*/

MethodL* new_method_l(char *id_method, char *label_method);

/**Funciones de Acceso a un Codigo*/

char* get_id_method(MethodL *methodl);
char* get_label_method(MethodL *methodl);

/**Funciones de Escritura de un Codigo*/

void set_id_method(MethodL *methodl, char *id_method);
void set_label_method(MethodL *methodl, char *label_method);


void to_string_method_l(MethodL *methodl);

#endif
