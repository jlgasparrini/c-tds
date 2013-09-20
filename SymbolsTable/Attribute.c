/*
	Implementation of STManagement.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Attribute.h"

/* creates a variable attribute containing the information included in the parameters */
Attribute* createVariable(char *id, PrimitiveType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Variable;
	(*attr).decl.variable.id = strdup(id);
	(*attr).decl.variable.type = type;
	return attr;
}

/* creates an array attribute containing the information included in the parameters */
Attribute* createArray(char *id, PrimitiveType type, unsigned int length)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Array;
	(*attr).decl.array.id = strdup(id);
	(*attr).decl.array.type = type; 
	(*attr).decl.array.length = length; 
	return attr;
}

/* creates a method attribute containing the information included in the parameters */
Attribute* createMethod(char *id, ReturnType type, unsigned char paramAmount)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Method;
	(*attr).decl.method.id = strdup(id);
	(*attr).decl.method.type = type; 
	(*attr).decl.method.paramSize = paramAmount;
	return attr;
}

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* createParameter(Attribute *attr, unsigned char pos, char *id, PrimitiveType type)
{
    if (pos < MAX_PARAMS-1)
    {  
		Attribute *aux = createVariable(id, type);
		addParameter(&(*attr).decl.method, &(*aux).decl.variable, pos);            
		return aux;
    } 
	printf("Ya se han alcanzado la cantidad maxima de parametros del metodo \"%s\".", (*attr).decl.method.id);
	return NULL;
}

/* Adds the "var" variable in the position "pos" of the method "method" */
void addParameter(StMethod *method, StVariable *var, unsigned char pos)
{
	pos++;
    (*method).parameters[pos] = *var;
    (*method).paramSize = pos; 
}

/* Sets the value of the variable that contains "attr" with the respective "value" */
void setVariableValue(Attribute *attr, PrimitiveType type, char *value)
{
	if (type == Int)
		(*attr).decl.variable.value.intVal = atoi(value);
	if (type == Float)
		(*attr).decl.variable.value.floatVal = atof(value);
	if (type == Bool)
	{
		if (strcmp(value, "false") == 0)
			(*attr).decl.variable.value.boolVal = False;
		else
			(*attr).decl.variable.value.boolVal = True;
	}
}
