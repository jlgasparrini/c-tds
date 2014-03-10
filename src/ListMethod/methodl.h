/**************************************************
*Define la estructura de el lebal de un metodo    *
*                                                 *
*Una label va a tener :                           *
* id	   	 :   identificador del metodo 		  *
* label      :   label del metodo		          *
**************************************************/

#ifndef methodl_H
#define methodl_H

#include <stdbool.h>

typedef struct {
    char *id;
    char *label;
} MethodL;


/**Constructor de un Codigo*/

MethodL* newMethodL(char *id_method, char *label_method);

/**Funciones de Acceso a un Codigo*/

char* getIdMethod(MethodL *methodl);
char* getLabelMethod(MethodL *methodl);

/**Funciones de Escritura de un Codigo*/

void setIdMethod(MethodL *methodl, char *id_method);
void setLabelMethod(MethodL *methodl, char *label_method);


void toStringMethodL(MethodL *methodl);

#endif
