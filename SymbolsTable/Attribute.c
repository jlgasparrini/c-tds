/*
	Implementation of Attribute.h
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

/* Creates a StVariable with the respective type and initialized */
StVariable createStVariable(PrimitiveType type)
{
	StVariable var; 
	var.type = type;
	if (type == Int)
		var.value.intVal = 0;
	if (type == Float)
		var.value.floatVal = 0.0;
	if (type == Bool)
		var.value.boolVal = False;
	return var;
}

/* creates an array attribute containing the information included in the parameters */
Attribute* createArray(char *id, PrimitiveType type, unsigned int length)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Array;
	(*attr).decl.array.id = strdup(id);
	(*attr).decl.array.type = type; 
	(*attr).decl.array.length = length;
	(*attr).decl.array.arrayValues = (StVariable*) malloc (length*sizeof(StVariable)); /* creates the necessary memory for the array */
	int i;
	for(i = 0; i < length; i++)
	{	// Initializes all the values of the array
		(*attr).decl.array.arrayValues[i] = createStVariable(type);
	}
	return attr;
}

/* creates a method attribute containing the information included in the parameters */
Attribute* createMethod(char *id, ReturnType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Method;
	(*attr).decl.method.id = strdup(id);
	(*attr).decl.method.type = type; 
	(*attr).decl.method.paramSize = 0;
	return attr;
}

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* createParameter(Attribute *attr, unsigned int pos, char *id, PrimitiveType type)
{
	if (attr != NULL)
	{
		Attribute *aux = createVariable(id, type);
		(*attr).decl.method.parameters[pos] = (*aux).decl.variable;
		return aux;
	}
	return NULL; /* The method doesn't exist. Null is returned. (could be informed to the errorQueue too) */
}

/* Sets the amount of parameters that will have the method attr */
void setAmountOfParameters(Attribute *attr, unsigned int amount)
{
    if ((*attr).type == Method)
		(*attr).decl.method.paramSize = amount;
}

/* Sets the value of the variable that contains "attr" with the respective "value" */
void setVariableValue(Attribute *attr, PrimitiveType type, char *value)
{
	if (type == Int)
		setIntVal(attr,atoi(value));
	if (type == Float)
		setFloatVal(attr,atof(value));
	if (type == Bool)
	{
		if (strcmp(value, "false") == 0)
			setBoolVal(attr,False);
		if (strcmp(value, "true") == 0)
			setBoolVal(attr,True);
	}
}

/* Returns the ID of the specified attribute */
char* getID(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*attr).decl.variable.id;
	if ((*attr).type == Method)
		return (*attr).decl.method.id;
	if ((*attr).type == Array)
		return (*attr).decl.array.id;

}

/* Returns the intVal of the attribute */
int getIntVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*attr).decl.variable.value.intVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.intVal;
}

/* Returns the floatVal of the attribute */
float getFloatVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*attr).decl.variable.value.floatVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.floatVal;
}

/* Returns the boolVal of the attribute */
Boolean getBoolVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*attr).decl.variable.value.boolVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.boolVal;
}

/* Sets the intVal of the attribute */
void setIntVal(Attribute *attr, int value)
{
	if ((*attr).type == Variable)
		(*attr).decl.variable.value.intVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.intVal = value;
}

/* Sets the floatVal of the attribute */
void setFloatVal(Attribute *attr, float value)
{
	if ((*attr).type == Variable)
		(*attr).decl.variable.value.floatVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.floatVal = value;
}

/* Sets the boolVal of the attribute */
void setBoolVal(Attribute *attr, Boolean value)
{
	if ((*attr).type == Variable)
		(*attr).decl.variable.value.boolVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.boolVal = value;
}
